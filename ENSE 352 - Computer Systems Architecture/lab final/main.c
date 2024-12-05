#include "main.h"
#include "stm32f10x.h"
#include <stdlib.h>    // For rand() and srand()
#include <stdbool.h>   // For bool type

// Global variables
int rnd = 1;                 // Current round
int seq[MAX_ROUNDS];         // Sequence of LEDs

int main(void) {
    initialize();

    while (1) {
        // Wait for user to start the game and seed the random number generator
        wait_for_user_input_and_seed();
        delay();
        delay();

        // Generate a random sequence of LEDs
        for (int i = 0; i < MAX_ROUNDS; i++) {
            seq[i] = randomNumberTo4();
        }

        // Play rounds until user fails or reaches MAX_ROUNDS
        while (rnd <= MAX_ROUNDS) {
            if (rounds(rnd)) {
                rnd++;
                delay();
                delay();
            } else {
                break; // User failed
            }
        }

        if (rnd > MAX_ROUNDS) {
            // User won the game after completing MAX_ROUNDS rounds
            for (int i = 0; i < 4; i++) {
                turnOn4LEDs();
                delay();
                turnOff4LEDs();
                delay();
            }
            winning();
            rnd = 1; // Reset the game
        } else {
            failing();
            rnd = 1; // Reset the game
        }
    }
}

// Delay functions
void startdelay(void) {
    for (int i = 0; i < 200000; i++) {
        // Simple delay loop
    }
}

void delay(void) {
    for (int x = 0; x < 1000000; x++) {
        // Simple delay loop
    }
}

// Button functions
bool buttonPress(void) {
    if (!(GPIOB->IDR & (1 << 4))) return true;   // Black button pressed
    if (!(GPIOB->IDR & (1 << 6))) return true;   // Red button pressed
    if (!(GPIOB->IDR & (1 << 8))) return true;   // Green button pressed
    if (!(GPIOB->IDR & (1 << 9))) return true;   // Blue button pressed
    return false;
}

int buttonSelect(void) {
    if (!(GPIOB->IDR & (1 << 4))) return 1;   // Black button
    if (!(GPIOB->IDR & (1 << 6))) return 2;   // Red button
    if (!(GPIOB->IDR & (1 << 8))) return 3;   // Green button
    if (!(GPIOB->IDR & (1 << 9))) return 4;   // Blue button
    return -1;
}

// Random number function
int randomNumberTo4(void) {
    return rand() % NUMBER_OF_LEDS;
}

// LED control functions
// Both were taken from milestone and reused
void turnOn4LEDs(void) {
    GPIOA->ODR |= (1 << 0);
		GPIOA->ODR |= (1 << 1); 
		GPIOA->ODR |= (1 << 4);
    GPIOB->ODR |= (1 << 0);
}

void turnOff4LEDs(void) {
    GPIOA->ODR &= ~(1 << 0);
		GPIOA->ODR &= ~(1 << 1); 
		GPIOA->ODR &= ~(1 << 4);
    GPIOB->ODR &= ~(1 << 0);
}

// Sequence functions
void starting(void) {
    // Light up LEDs in sequence
    for (int i = 0; i < 4; i++) {
        if (i == 0) {
            GPIOA->ODR |= (1 << 0);  // Turn on LED at A0
        } else if (i == 1) {
            GPIOA->ODR |= (1 << 1);  // Turn on LED at A1
        } else if (i == 2) {
            GPIOA->ODR |= (1 << 4);  // Turn on LED at A4
        } else if (i == 3) {
            GPIOB->ODR |= (1 << 0);  // Turn on LED at B0
        }
        startdelay();
        // Turn off all LEDs
        turnOff4LEDs();
    }
    // Light up LEDs in reverse sequence
    for (int i = 3; i >= 0; i--) {
        if (buttonPress()) {
            return;  // Exit if any button is pressed
        }
        if (i == 0) {
            GPIOA->ODR |= (1 << 0);  // Turn on LED at A0
        } else if (i == 1) {
            GPIOA->ODR |= (1 << 1);  // Turn on LED at A1
        } else if (i == 2) {
            GPIOA->ODR |= (1 << 4);  // Turn on LED at A4
        } else if (i == 3) {
            GPIOB->ODR |= (1 << 0);  // Turn on LED at B0
        }
        startdelay();
        // Turn off all LEDs
        turnOff4LEDs();
    }
}

void failing(void) {
    // Flash inner and outer LEDs alternately 4 times
    for (int i = 0; i < 4; i++) {
        // Turn on inner LEDs
        GPIOA->ODR |= (1 << 1) | (1 << 4);
        delay();
        // Turn off all LEDs
        turnOff4LEDs();

        // Turn on outer LEDs
        GPIOA->ODR |= (1 << 0);
        GPIOB->ODR |= (1 << 0);
        delay();
        // Turn off all LEDs
        turnOff4LEDs();
    }

    // Display the round achieved in binary on LEDs
    if (((rnd - 1) >> 3) & 1)
        GPIOA->ODR |= (1 << 0);
    else
        GPIOA->ODR &= ~(1 << 0);

    if (((rnd - 1) >> 2) & 1)
        GPIOA->ODR |= (1 << 1);
    else
        GPIOA->ODR &= ~(1 << 1);

    if (((rnd - 1) >> 1) & 1)
        GPIOA->ODR |= (1 << 4);
    else
        GPIOA->ODR &= ~(1 << 4);

    if ((rnd - 1) & 1)
        GPIOB->ODR |= (1 << 0);
    else
        GPIOB->ODR &= ~(1 << 0);

    while (!buttonPress()) {
        // Wait for user to go back to main
    }

    // Turn off all LEDs after user presses a button
    turnOff4LEDs();
}

void winning(void) {
    // Display the number 10 in binary on LEDs (binary 1010)
    GPIOA->ODR |= (1 << 0);      // Bit 3: 1
    GPIOA->ODR &= ~(1 << 1);     // Bit 2: 0
    GPIOA->ODR |= (1 << 4);      // Bit 1: 1
    GPIOB->ODR &= ~(1 << 0);     // Bit 0: 0

    // Wait for user to press any button
    while (!buttonPress()) {
        // Do nothing, just wait
    }

    // Turn off all LEDs after user presses a button
    turnOff4LEDs();
}

// Wait function
void wait_for_user_input_and_seed(void) {
    unsigned int seed = 0;
    while (1) {
        starting();
        // Increment seed counter
        seed++;
        if (buttonPress()) {
            break;  // Exit when any button is pressed
        }
    }
    // Seed the random number generator with the seed value
		// Makes it so that the numbers are always random and does not have repeating sequence
    srand(seed);
}

// Game function
bool rounds(int round) {
    // Show the sequence to the user
    for (int i = 0; i < round; i++) {
        int light = seq[i];
        switch (light) {
            case 0:
                GPIOA->ODR |= (1 << 0);
                delay();
                GPIOA->ODR &= ~(1 << 0);
                break;
            case 1:
                GPIOA->ODR |= (1 << 1);
                delay();
                GPIOA->ODR &= ~(1 << 1);
                break;
            case 2:
                GPIOA->ODR |= (1 << 4);
                delay();
                GPIOA->ODR &= ~(1 << 4);
                break;
            case 3:
                GPIOB->ODR |= (1 << 0);
                delay();
                GPIOB->ODR &= ~(1 << 0);
                break;
        }
        delay();
    }

    // Validate user input with a simple timeout
    for (int i = 0; i < round; i++) {
        int whichbut = -1;
        int timeout = 0;
        while (whichbut == -1 && timeout < 2700000) {
            whichbut = buttonSelect();
            timeout++;
        }

        // Check if timeout occurred
        if (whichbut == -1) {
            return false;  // Timeout failure
        }

        int userInput = whichbut - 1;  // Adjust to 0-based index

        // Check if current input matches the expected sequence
        if (userInput != seq[i]) {
            return false;  // User input incorrect
        }

        // Light up the LED corresponding to the button pressed
        switch (userInput) {
            case 0:
                GPIOA->ODR |= (1 << 0);
                delay();
                GPIOA->ODR &= ~(1 << 0);
                break;
            case 1:
                GPIOA->ODR |= (1 << 1);
                delay();
                GPIOA->ODR &= ~(1 << 1);
                break;
            case 2:
                GPIOA->ODR |= (1 << 4);
                delay();
                GPIOA->ODR &= ~(1 << 4);
                break;
            case 3:
                GPIOB->ODR |= (1 << 0);
                delay();
                GPIOB->ODR &= ~(1 << 0);
                break;
        }
    }

    return true;  // User input correct for the entire round
}

void initialize(){
	// Enable clocks for GPIO ports A, B, and C
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

    // Configure GPIOA pins A0, A1, A4 as outputs (LEDs)
    GPIOA->CRL &= ~((0xF << (4 * 0)) | (0xF << (4 * 1)) | (0xF << (4 * 4)));
    GPIOA->CRL |=  ((0x3 << (4 * 0)) | (0x3 << (4 * 1)) | (0x3 << (4 * 4)));

    // Configure GPIOB pins B0 as output (LED), B4, B6, B8, B9 as inputs (Buttons)
    GPIOB->CRL &= ~((0xF << (4 * 0)) | (0xF << (4 * 4)) | (0xF << (4 * 6)));
    GPIOB->CRL |=  (0x3 << (4 * 0));                                  
    GPIOB->CRL |=  ((0x4 << (4 * 4)) | (0x4 << (4 * 6)));                   
    GPIOB->CRH &= ~((0xF << (4 * 0)) | (0xF << (4 * 1)));            
    GPIOB->CRH |=  ((0x4 << (4 * 0)) | (0x4 << (4 * 1)));
}