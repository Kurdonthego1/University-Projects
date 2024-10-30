// Model (Data) Section
let notes = [];
let currentUser = 'User A';
let noteIdCounter = 3;  // To keep track of unique IDs for new notes

// Controller Section
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
        "score": 0,
        "has-voted": false  // Flag to track if the current user has voted
    };

    notes.push(newNote);  // Add the new note to the notes array
    document.getElementById('new-note-text').value = '';  // Clear input field
    renderNotes();  // Re-render notes
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
    note['has-voted'] = true;  // Mark that the current user has voted
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
    note['has-voted'] = true;  // Mark that the current user has voted
    renderNotes();
}

// View Section
function renderNotes() {
    const noteContainer = document.getElementById('note-container');
    noteContainer.innerHTML = '';  // Clear the container before re-rendering

    notes.forEach(note => {
        const noteElement = document.createElement('div');
        noteElement.className = 'lineofinput';
        noteElement.style.padding = '5px';

        const canVote = currentUser !== note['note-creator'];  // User can't vote on their own notes
        const score = note['upvote-user'].length - note['downvote-user'].length;

        // Determine the appropriate class for buttons based on voting status
        const upvoteClass = note['upvote-user'].includes(currentUser) ? 'upvote-active' : '';
        const downvoteClass = note['downvote-user'].includes(currentUser) ? 'downvote-active' : '';

        // Display score only if the user has voted
        const scoreDisplay = note['has-voted'] && (note['upvote-user'].includes(currentUser) || note['downvote-user'].includes(currentUser)) ? score : '';

        // Create note element structure
        noteElement.innerHTML = `
            <input type="text" class="inputbox" value="${note['note-text']}" disabled>
            <input type="button" class="up ${upvoteClass}" value="↑" onclick="upvote(${note['note-identifier']})" ${!canVote ? 'disabled' : ''}>
            <input type="button" class="down ${downvoteClass}" value="↓" onclick="downvote(${note['note-identifier']})" ${!canVote ? 'disabled' : ''}>
            <input type="button" class="score" value="${scoreDisplay}">
        `;

        noteContainer.appendChild(noteElement);  // Add the note to the container
    });
}

// Initial rendering
renderNotes();
