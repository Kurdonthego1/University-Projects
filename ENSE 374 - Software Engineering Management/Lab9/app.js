const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static('public'));
app.use(express.urlencoded({ extended: true }));
app.set('view engine', 'ejs');

// Load posts from JSON file
let posts = [];
try {
    const data = fs.readFileSync('posts.json', 'utf8');
    posts = JSON.parse(data);
} catch (err) {
    console.error('Error reading posts JSON file:', err);
}

// Load users from JSON file
let users = [];
try {
    const data = fs.readFileSync('users.json', 'utf8');
    users = JSON.parse(data);
} catch (err) {
    console.error('Error reading users JSON file:', err);
}

// Function to save posts to JSON file
function savePosts() {
    fs.writeFileSync('posts.json', JSON.stringify(posts, null, 2), 'utf8');
}

// Route to serve the login page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'login.html'));
});

// Logout route
app.post('/logout', (req, res) => {
    res.redirect('/');
});

app.post('/note-vote', (req, res) => {
    const username = req.body.username || req.query.username;
    if (!username) {
        return res.redirect('/');
    }
    res.render('notevote', { username, posts });
});

// POST route to handle login
app.post('/login', (req, res) => {
    const username = req.body.username;
    const password = req.body.password;
    let user = null;

    for (let i = 0; i < users.length; i++) {
        if (users[i].username === username && users[i].password === password) {
            user = users[i];
            break;
        }
    }

    if (user) {
        res.render('notevote', { username, posts });
    } else {
        res.redirect('/');
    }
});

// POST route to add a new post
app.post('/addpost', (req, res) => {
    const username = req.body.username;
    const text = req.body.text;

    const newPost = {
        _id: posts.length + 1,
        text: text,
        creator: { username: username },
        upvotes: [],
        downvotes: []
    };

    posts.push(newPost);
    savePosts();
    res.render('notevote', { username, posts });
});

// Route to handle upvoting a post
app.post('/upvote', (req, res) => {
    const postId = parseInt(req.body.postId);
    const username = req.body.username;

    for (let i = 0; i < posts.length; i++) {
        if (posts[i]._id === postId && posts[i].creator.username !== username) {
            let upvoteIndex = posts[i].upvotes.indexOf(username);
            let downvoteIndex = posts[i].downvotes.indexOf(username);

            if (downvoteIndex !== -1) {
                posts[i].downvotes.splice(downvoteIndex, 1);
            }
            if (upvoteIndex === -1) {
                posts[i].upvotes.push(username);
            }
            break;
        }
    }

    savePosts();
    res.redirect(307, `/note-vote?username=${username}`);
});

// Route to handle removing an upvote
app.post('/remove-upvote', (req, res) => {
    const postId = parseInt(req.body.postId);
    const username = req.body.username;

    for (let i = 0; i < posts.length; i++) {
        if (posts[i]._id === postId) {
            let upvoteIndex = posts[i].upvotes.indexOf(username);
            if (upvoteIndex !== -1) {
                posts[i].upvotes.splice(upvoteIndex, 1);
            }
            break;
        }
    }

    savePosts();
    res.redirect(307, `/note-vote?username=${username}`);
});

// Route to handle downvoting a post
app.post('/downvote', (req, res) => {
    const postId = parseInt(req.body.postId);
    const username = req.body.username;

    for (let i = 0; i < posts.length; i++) {
        if (posts[i]._id === postId && posts[i].creator.username !== username) {
            let upvoteIndex = posts[i].upvotes.indexOf(username);
            let downvoteIndex = posts[i].downvotes.indexOf(username);

            if (upvoteIndex !== -1) {
                posts[i].upvotes.splice(upvoteIndex, 1);
            }
            if (downvoteIndex === -1) {
                posts[i].downvotes.push(username);
            }
            break;
        }
    }

    savePosts();
    res.redirect(307, `/note-vote?username=${username}`);
});

// Route to handle removing a downvote
app.post('/remove-downvote', (req, res) => {
    const postId = parseInt(req.body.postId);
    const username = req.body.username;

    for (let i = 0; i < posts.length; i++) {
        if (posts[i]._id === postId) {
            let downvoteIndex = posts[i].downvotes.indexOf(username);
            if (downvoteIndex !== -1) {
                posts[i].downvotes.splice(downvoteIndex, 1);
            }
            break;
        }
    }

    savePosts();
    res.redirect(307, `/note-vote?username=${username}`);
});

const mongoose = require('mongoose');
mongoose.connect('mongodb://localhost:27017/test');

const userSchema = new mongoose.userSchema({
    username: String,
    password: String
});

const Users = mongoose.model("Users", userSchema);

const postsSchema = new mongoose.Schema({
    text: String,
    user: userSchema,
    upvotes: [userSchema],
    downvotes: [userSchema]
});

const Posts = mongoose.model("Posts", postsSchema);

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
