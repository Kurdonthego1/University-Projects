const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = 3000;

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static('public'));
app.use(express.urlencoded({ extended: true }));
app.set('view engine', 'ejs');

const mongoose = require('mongoose');
mongoose.connect('mongodb://localhost:27017/test');

// User Schema with validation
const userSchema = new mongoose.Schema({
    username: { type: String, required: true, unique: true },
    password: { type: String, required: true },
});

const Users = mongoose.model("User", userSchema);

const postSchema = new mongoose.Schema({
    text: {type: String},
    user: userSchema,
    upvotes: [userSchema],
    downvotes: [userSchema]
});

const Posts = mongoose.model("Post", postSchema);

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

// Function to save users to JSON file
function saveUsers() {
    fs.writeFileSync('users.json', JSON.stringify(users, null, 2), 'utf8');
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

app.post('/register', async (req, res) => {
    const { usernamereg, passwordreg, invitecodereg } = req.body;

    if (invitecodereg !== "code") {
        console.log("Invalid invite code");
        return res.redirect('/');
    }

    try {
        const existingUser = await Users.findOne({ username: usernamereg });
        if (existingUser) {
            console.log("User already exists");
            return res.redirect('/');
        }

        const newUser = new Users({ username: usernamereg, password: passwordreg });
        await newUser.save();
        console.log("New user registered:", usernamereg);

        res.redirect('/');
    } catch (error) {
        console.error("Error registering user:", error);
        res.status(500).send("Internal Server Error");
    }
});


// Handle login
app.post('/login', async (req, res) => {
    const { username, password } = req.body;

    try {
        // Validate user credentials
        const user = await Users.findOne({ username, password });
        if (user) {
            console.log("Login successful for user:", username);
            res.render('notevote', { username, posts });
        } else {
            console.log("Invalid username or password");
            res.redirect('/');
        }
    } catch (error) {
        console.error("Error during login:", error);
        res.status(500).send("Internal Server Error");
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


// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
