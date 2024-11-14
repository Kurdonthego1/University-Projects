const mongoose = require ( 'mongoose' );

mongoose.connect( 'mongodb://localhost:27017/test');

const userSchema = new mongoose.Schema({
    username: String,
    password: String
});

const Users = mongoose.model( "Users", userSchema);

const postsSchema = new mongoose.Schema({
    text: String,
    user: userSchema,
    upvotes: [userSchema],
    downvotes: [userSchema]
})

const Posts = mongoose.model( "Posts", postsSchema);

const user = new Users({
    username: "demo",
    password: "12345"
});

const post = new Posts({
    text: "emo txt",
    user: user,
    upvotes: [],
    downvotes: []
});

user.save();
post.save();
