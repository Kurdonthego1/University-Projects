let button = document.getElementsByClassName("btn btn-primary")[0];
let colors = ["#8fdf3f", "#ff65a3", "#7afcff", "#feff9c", "#fff740"];
let colorIndex = 0;

// Event listener for the button click
button.addEventListener("click", buttonClick);

// Function to handle button click and create a new card
function buttonClick() {
  // Selecting title and note content fields
  let title = document.getElementsByClassName("form-title")[0].value;
  let noteContent = document.getElementsByClassName("post-area")[0].value;

  // Make a new card if title and content are not empty
  if (title && noteContent) {
    let newCard = createCard(title, noteContent);
    document.getElementsByClassName("notes-container")[0].appendChild(newCard);
  }
}

// Function to create a new card element
function createCard(title, content) {
  // Create the card container
  let newNote = document.createElement("div");
  newNote.classList.add("card");
  newNote.style.width = "200px";
  newNote.style.margin = "10px";
  newNote.style.backgroundColor = colors[colorIndex];

  colorIndex = (colorIndex + 1) % colors.length;

  // Create the card body
  let cardBody = document.createElement("div");
  cardBody.classList.add("card-body");

  let noteTitle = document.createElement("h2");
  noteTitle.classList.add("note-title");
  noteTitle.innerText = title;

  let noteText = document.createElement("p");
  noteText.classList.add("note-text");
  noteText.innerText = content;

  let burn = burnButton(newNote);

  cardBody.appendChild(noteTitle);
  cardBody.appendChild(noteText);
  cardBody.appendChild(burn);

  newNote.appendChild(cardBody);

  return newNote;
}

// Function to create the burn button and add its functionality
function burnButton(noteElement) {
  let burn = document.createElement("button");
  burn.classList.add("btn", "btn-danger");
  burn.innerText = "🔥";

  // Add event listener to remove the note when the button is clicked
  burn.addEventListener("click", function () {
    noteElement.remove();
  });

  return burn;
}