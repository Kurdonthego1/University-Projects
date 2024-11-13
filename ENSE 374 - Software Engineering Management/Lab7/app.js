const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static('public'));
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

// Route to serve the login page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'login.html'));
});

app.post('/note-vote', (req, res) => {
    const posts = loadPosts();
    const username = req.body.username || req.query.username; // Retrieve username from the request body or query
    res.render('notevote', { username, posts });
});

// POST route to handle login
app.post('/login', (req, res) => {
    const { username, password } = req.body;
    const users = loadUsers();
    const user = users.find(u => u.username === username && u.password === password);

    if (user) {
        res.render('notevote', { username, posts: loadPosts() });  // Render directly with username and posts
    } else {
        res.redirect('/');  // Redirect back to login on failure
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
    res.render('notevote', { username, posts }); // Render directly with username and posts
});


// Route to handle upvoting a post
app.post('/upvote', (req, res) => {
    const { postId } = req.body;
    const { username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post) {
        // Remove user from downvotes if present and add to upvotes if not already there
        post.downvotes = post.downvotes.filter(user => user !== username);
        if (!post.upvotes.includes(username)) {
            post.upvotes.push(username);
        }
    }

    savePosts(posts);
    res.redirect(307, `/note-vote?username=${username}`);

});

// Route to handle removing an upvote
app.post('/remove-upvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post) {
        post.upvotes = post.upvotes.filter(user => user !== username);
    }

    savePosts(posts);
    res.redirect(307, `/note-vote?username=${username}`);

});

// Route to handle downvoting a post
app.post('/downvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post) {
        // Remove user from upvotes if present and add to downvotes if not already there
        post.upvotes = post.upvotes.filter(user => user !== username);
        if (!post.downvotes.includes(username)) {
            post.downvotes.push(username);
        }
    }

    savePosts(posts);
    res.redirect(307, `/note-vote?username=${username}`);

});

// Route to handle removing a downvote
app.post('/remove-downvote', (req, res) => {
    const { postId, username } = req.body;
    const posts = loadPosts();

    const post = posts.find(p => p._id === parseInt(postId));
    if (post) {
        post.downvotes = post.downvotes.filter(user => user !== username);
    }

    savePosts(posts);
    res.redirect(307, `/note-vote?username=${username}`);

});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
