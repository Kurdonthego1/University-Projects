const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.urlencoded({ extended: true }));
app.set('view engine', 'ejs');

// Helper function to load posts from JSON file
function loadPosts() {
    try {
        const data = fs.readFileSync('posts.json', 'utf8');
        return JSON.parse(data);
    } catch (err) {
        console.error('Error reading posts JSON file:', err);
        return [];
    }
}

// Helper function to save posts to JSON file
function savePosts(posts) {
    fs.writeFileSync('posts.json', JSON.stringify(posts, null, 2), 'utf8');
}

// Helper function to load users from JSON file
function loadUsers() {
    try {
        const data = fs.readFileSync('users.json', 'utf8');
        return JSON.parse(data);
    } catch (err) {
        console.error('Error reading users JSON file:', err);
        return [];
    }
}

// Helper function to save users to JSON file
function saveUsers(users) {
    fs.writeFileSync('users.json', JSON.stringify(users, null, 2), 'utf8');
}

// Route to serve the login page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'login.html'));
});

app.get('/logout', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'login.html'));
});

// POST route to handle login and registration
app.post('/login', (req, res) => {
    const { username, password, invitecode } = req.body;
    const users = loadUsers();

    // Check if the request is for registration (invitecode field is filled)
    if (invitecode) {
        // Registration process
        if (invitecode === "code") { // Verify invite code
            // Add the new user
            const newUser = { username, password };
            users.push(newUser);
            saveUsers(users); // Save the updated user list to users.json
            res.redirect('/notevote', { username, posts: loadPosts() }); // Redirect to login page after successful registration
        } else {
            res.redirect('/'); // Incorrect invite code, redirect to login page
        }
    } else {
        // Login process
        const user = users.find(u => u.username === username && u.password === password);

        if (user) {
            res.render('notevote', { username, posts: loadPosts() });
        } else {
            res.redirect('/');
        }
    }
});

// POST route to add a new post
app.post('/addpost', (req, res) => {
    const { username, text } = req.body;
    const posts = loadPosts();

    const newPost = {
        _id: posts.length + 1,
        text: text,
        creator: { username: username },
        upvotes: [],
        downvotes: []
    };

    posts.push(newPost);
    savePosts(posts);
    res.render('notevote', { username, posts });
});

// Route to handle upvoting a post
app.post('/upvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post && post.creator.username !== username) {  // Ensure the user is not the post creator
        post.downvotes = post.downvotes.filter(user => user !== username);
        if (!post.upvotes.includes(username)) {
            post.upvotes.push(username);
        }
        savePosts(posts);
    }
    res.redirect(307, `/note-vote?username=${username}`);
});

// Route to handle removing an upvote
app.post('/remove-upvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post) {
        post.upvotes = post.upvotes.filter(user => user !== username);
        savePosts(posts);
    }
    res.redirect(307, `/note-vote?username=${username}`);
});

// Route to handle downvoting a post
app.post('/downvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post && post.creator.username !== username) {  // Ensure the user is not the post creator
        post.upvotes = post.upvotes.filter(user => user !== username);
        if (!post.downvotes.includes(username)) {
            post.downvotes.push(username);
        }
        savePosts(posts);
    }
    res.redirect(307, `/note-vote?username=${username}`);
});

// Route to handle removing a downvote
app.post('/remove-downvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post) {
        post.downvotes = post.downvotes.filter(user => user !== username);
        savePosts(posts);
    }
    res.redirect(307, `/note-vote?username=${username}`);
});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
