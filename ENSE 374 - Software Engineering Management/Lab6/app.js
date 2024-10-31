const express = require('express');
const fs = require('fs');
const path = require('path');
const app = express();
const PORT = 3000;

// Serve static files from the "public" directory
app.use(express.static(path.join(__dirname, 'public')));
app.use(express.urlencoded({ extended: true }));

// Route to serve the login page
app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'login.html'));
});

// Route to serve the application page after successful login
app.get('/app', (req, res) => {
    res.sendFile(path.join(__dirname, 'public', 'notevote.html'));
});

// POST route to handle login
app.post('/login', (req, res) => {
    const { username, password } = req.body;

    fs.readFile('users.json', 'utf8', (err, data) => {
        if (err) {
            console.error('Error reading JSON file:', err);
            res.status(500).send('Internal server error');
            return;
        }

        const users = JSON.parse(data);
        const user = users.find(u => u.username === username && u.password === password);

        if (user) {
            res.redirect('/app');  // Redirect to app page on successful login
        } else {
            res.redirect('/');  // Redirect back to login on failure
        }
    });
});

// Start the server
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
