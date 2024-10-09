// // Wait until the page is fully loaded
// document.addEventListener("DOMContentLoaded", function() {
//     const colors = ["#f7feb9", "#ff65a3", "#7afcff", "#feff9c", "#fff740"];
//     let colorIndex = 0; // Keeps track of the current color
//     const notesContainer = document.querySelector(".notes-container");

//     // Function to add a new note
//     const addNote = (title, content) => {
//       // Create a new note element
//       const note = document.createElement("div");
//       note.className = "card mb-3";
//       note.style.backgroundColor = colors[colorIndex];
//       colorIndex = (colorIndex + 1) % colors.length; // Move to the next color

//       // Set the note content
//       note.innerHTML = `
//         <div class="card-body">
//           <h5 class="card-title">${title}</h5>
//           <p class="card-text">${content}</p>
//           <button type="button" class="btn btn-danger burn-btn">Burn</button>
//         </div>
//       `;

//       // Add functionality to the "Burn" button
//       note.querySelector(".burn-btn").addEventListener("click", () => {
//         note.remove(); // Remove the note from the view
//       });

//       // Add the note to the container
//       notesContainer.appendChild(note);
//     };

//     // Handle the "Post!" button click
//     document.querySelector(".btn-primary").addEventListener("click", () => {
//       const titleInput = document.querySelector(".form-title");
//       const contentInput = document.querySelector(".post-area");

//       const title = titleInput.value.trim();
//       const content = contentInput.value.trim();

//       if (title && content) {
//         addNote(title, content); // Add a new note
//         titleInput.value = ""; // Clear the input fields
//         contentInput.value = "";
//       }
//     });
// });


// Selecting necessary elements by the correct class and id names
let button = document.getElementsByClassName("btn btn-primary")[0];
let colors = ["#ff7eb9", "#ff65a3", "#7afcff", "#feff9c", "#fff740"];
let color = 1;

button.addEventListener("click", function () {
  console.log("Button clicked!");

  // Correcting the selection of title and note content fields
  let title = document.getElementsByClassName("form-title")[0].value;
  let noteContent = document.getElementsByClassName("post-area")[0].value;

  // Making the new card and adding it
  if (title || noteContent) {
    // Creating the added note container
    let newNote = document.createElement("div");
    newNote.classList.add("card");
    newNote.style.width = "18rem";
    newNote.style.margin = "10px"; // Adding a small margin for better spacing

    // Creating card body for card
    let cardBody = document.createElement("div");
    cardBody.classList.add("card-body");

    // Creating HTML element for posted note title
    let noteTitle = document.createElement("h2");
    noteTitle.classList.add("note-title");
    noteTitle.innerText = title;

    // Creating HTML element for posted note content
    let noteText = document.createElement("p");
    noteText.classList.add("note-text");
    noteText.innerText = noteContent;

    // Creating Burn Button
    let burnButton = document.createElement("button");
    burnButton.classList.add("btn", "btn-danger");
    burnButton.innerText = "🔥";

    // Add event listener for burn button
    burnButton.addEventListener("click", function () {
      newNote.remove(); // Removes the note when button is clicked
    });

    // Append all elements to newNote
    cardBody.appendChild(noteTitle);
    cardBody.appendChild(noteText);
    cardBody.appendChild(burnButton);
    newNote.appendChild(cardBody);

    // Display the new note in the notes container
    document.getElementsByClassName("notes-container")[0].appendChild(newNote);
  }
});
