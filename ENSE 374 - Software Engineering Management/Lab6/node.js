const express = require("express");
const app = express();
const port = 3000;

app.use(express.static("public"))
app.use(express.urlencoded({ extended: true}));

app.get("/", (req, res) => {
    res.sendFile(__dirname + "/login.html")
    console.log("A user requested the about page");
});

app.post ("/", (req, res) => {
    if (req.body["emailtext"] === "secret") {
        res.redirect(307, "/secret")
    }

});




app.listen (port, () => {
    console.log (`Server is running on http://localhost:${port}`);
});


