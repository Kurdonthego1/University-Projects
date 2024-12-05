<h2 div align="center">

Simon Says - ENSE 352 Lab Project

</div>

### **Project Descrition:**

This project was made for ENSE 352 - Computer Systems Architecture Lab Final and is based off of Simon.

Simon is a game built to test short-term memory retention as well as the ability to follow a sequence of LEDs.

As each round progresses you must remember the sequence before and add the new button to input.

In order to win you must complete 10 rounds without failure, one wrong input will result in failure.

[Demonstration and Showcase]("https://www.youtube.com/watch?v=5D9F1n3j_YY")

### **STM and Breadboard:**

Simon was recreated using:
- STM32F103RB
- Breadboard
- 270 Ohm Resistor
- 10K Ohm Bus Resistor
- 4 LED's
- 4 Buttons

Project was compiled and built in C using Keil Vision.

In order to initiate the game the above mentioned components must follow the [schematic]("https://github.com/Kurdonthego1/University-Projects/blob/main/ENSE%20352%20-%20Computer%20Systems%20Architecture/lab%20final/Simon%20Game%20Schematic.pdf")

### **How to play?**

After the circuit is built and the file, main.c, is loaded on you may initiate the game.

**Starting:**
- Starting sequence imitates the [Knight Rider]("https://youtu.be/oNyXYPhnUIs?si=Uq93w3tZsj_MqU3o&t=9") LED sequence.- At this point, any input from the 4 buttons will start the game
- From there you must follow the pattern and input what Simon Says

**Winning:**
- In order to win you must complete 10 rounds
- After 10 rounds the LEDs will blink all on and all off 4 times
- The level reached will be shown in binary, in the winnning case you will see "10" or 1010
- Press any button to restart the initial starting sequence and play the game again!

**Rounds:**
- Simon will have 10 rounds
- You will have 5 seconds between each input to press a button, if it is wrong you fail and must restart
- Every correct sequence will add 1 more LED until the 10th round, beat it and you win Simon!

**Losing:**
- If at any point you make a mistake and cannot repeat the sequence the game will commence the failure sequence
- LEDs will blink in the following order
    - Inner 2 LEDs
    - Followed by a pause
    - Outer 2 LEDs
    - This will repeat 4 times
- The level reached will be displayed in binary once again, reach level 5? 0101 will be displayed to you
- Press any button to restart the initial starting sequence and play the game again!

