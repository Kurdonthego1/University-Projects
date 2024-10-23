let notes = [
    {
        "note-identifier": 1,
        "note-creator": "User A",
        "note-text": "Greatest HW",
        "upvote-user": [],
        "downvote-user": [],
        "score": 0
    },
    {
        "note-identifier": 2,
        "note-creator": "User B",
        "note-text": "Goat of LW",
        "upvote-user": [],
        "downvote-user": [],
        "score": 0
    }
];

let currentUser = 'User A';
let noteIdCounter = 3;  // To keep track of unique IDs for new notes

function switchUser(user) {
    currentUser = user;
    document.getElementById('logged-in-user').textContent = user;
    renderNotes();
}

function addNewNote() {
    const newNoteText = document.getElementById('new-note-text').value.trim();
    if (newNoteText === "") return; // Do not add empty notes

    const newNote = {
        "note-identifier": noteIdCounter++,  // Simple incrementing ID
        "note-creator": currentUser,
        "note-text": newNoteText,
        "upvote-user": [],
        "downvote-user": [],
        "score": 0
    };

    notes.push(newNote);  // Add the new note to the notes array
    document.getElementById('new-note-text').value = '';  // Clear input field
    renderNotes();  // Re-render notes
}

function renderNotes() {
    const noteContainer = document.getElementById('note-container');
    noteContainer.innerHTML = '';  // Clear the container before re-rendering

    notes.forEach(note => {
        const noteElement = document.createElement('div');
        noteElement.className = 'lineofinput';

        const canVote = currentUser !== note['note-creator'];  // User can't vote on their own notes
        const score = note['upvote-user'].length - note['downvote-user'].length;

        // Determine the appropriate class for buttons based on voting status
        const upvoteClass = note['upvote-user'].includes(currentUser) ? 'upvote-active' : '';
        const downvoteClass = note['downvote-user'].includes(currentUser) ? 'downvote-active' : '';

        // Create note element structure
        noteElement.innerHTML = `
            <input type="text" class="inputbox" value="${note['note-text']}" disabled>
            <input type="button" class="up ${upvoteClass}" value="↑" onclick="upvote(${note['note-identifier']})" ${!canVote ? 'disabled' : ''}>
            <input type="button" class="down ${downvoteClass}" value="↓" onclick="downvote(${note['note-identifier']})" ${!canVote ? 'disabled' : ''}>
            <input type="button" class="score" value="${score}">
        `;

        noteContainer.appendChild(noteElement);  // Add the note to the container
    });
}

function upvote(noteId) {
    const note = notes.find(n => n['note-identifier'] === noteId);
    if (!note || currentUser === note['note-creator']) return;

    // Toggle upvote: if already upvoted, remove it; if not, add upvote
    if (note['upvote-user'].includes(currentUser)) {
        note['upvote-user'] = note['upvote-user'].filter(user => user !== currentUser);
    } else {
        note['upvote-user'].push(currentUser);
        note['downvote-user'] = note['downvote-user'].filter(user => user !== currentUser); // Remove downvote if present
    }
    renderNotes();
}

function downvote(noteId) {
    const note = notes.find(n => n['note-identifier'] === noteId);
    if (!note || currentUser === note['note-creator']) return;

    // Toggle downvote: if already downvoted, remove it; if not, add downvote
    if (note['downvote-user'].includes(currentUser)) {
        note['downvote-user'] = note['downvote-user'].filter(user => user !== currentUser);
    } else {
        note['downvote-user'].push(currentUser);
        note['upvote-user'] = note['upvote-user'].filter(user => user !== currentUser); // Remove upvote if present
    }
    renderNotes();
}

// Initial rendering
renderNotes();
