#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stm32f10x.h>

void delay(){
	for (int x = 0; x < 100000; x++) { 
		// Nothing in the loop as its used for delay
		}
}

void user_delay(){
	for (int i = 0; i < 5000000; i++){
		// Nothing in the loop as its used for delay
		}
}

void turn_all_on(){
	GPIOA->ODR |= (1 << 0);
	GPIOA->ODR |= (1 << 1);
	GPIOA->ODR |= (1 << 4);
	GPIOB->ODR |= (1 << 0);
}

void turn_all_off(){
	GPIOA->ODR &= ~(1 << 0);
	GPIOA->ODR &= ~(1 << 1);
	GPIOA->ODR &= ~(1 << 4);
	GPIOB->ODR &= ~(1 << 0);
}	


void start_procedure(){
		GPIOA->ODR |= (1 << 0); // First LED on
		delay();
		// Second Sequence
		GPIOA->ODR |= (1 << 1); // Second LED on
		delay();
		GPIOA->ODR &= ~(1 << 0); // First LED off
		GPIOA->ODR |= (1 << 4); // Third LED on
		delay();
		// Third Sequence
		GPIOA->ODR &= ~(1 << 1); // Second LED off
		GPIOB->ODR |= (1 << 0); // Fourth LED on
		delay();
		// Fourth Sequence
		GPIOA->ODR &= ~(1 << 4); // Third LED off
		delay();
		// Backward Sequence
		GPIOA->ODR |= (1 << 4); // Third LED on
		delay();
		GPIOB->ODR &= ~(1 << 0); // Fourth LED off
		GPIOA->ODR |= (1 << 1); // Second LED on
		delay();
		GPIOA->ODR &= ~(1 << 4); // Third LED off
		GPIOA->ODR |= (1 << 0); // First LED on
		delay();
		GPIOA->ODR &= ~(1 << 1); // Second LED off
}

void wait_for_user_input() {
    while (1) {
        start_procedure(); // Keep looping the start procedure

        // Check for any button press (adjust pins as per your board's setup)
        if (!(GPIOB->IDR & (1 << 4)) ||  // Black Button
            !(GPIOB->IDR & (1 << 6)) ||  // Red Button
            !(GPIOB->IDR & (1 << 8)) ||  // Green Button
            !(GPIOB->IDR & (1 << 9))) {  // Blue Button
            break;
        }
    }
}

void winning_sequence(){
	for (int i = 0; i < 4; i++){
		turn_all_on();
		delay();
		turn_all_off();
		delay();
	}	
}

void failure_sequence() {
	for (int i = 0; i < 3; i++){
		GPIOA->ODR |= (1 << 0);
		GPIOA->ODR |= (1 << 4);
		delay();
		GPIOA->ODR &= ~(1 << 0);
		GPIOA->ODR &= ~(1 << 4);
		delay();
		GPIOA->ODR |= (1 << 1);
		GPIOB->ODR |= (1 << 0);
		delay();
		GPIOA->ODR &= ~(1 << 1);
		GPIOB->ODR &= ~(1 << 0);
	}	
}
	// &= ~ Turns it off

	// Black Button            // First LED
	// GPIOB->IDR & (1 << 4)   // GPIOA->ODR |= (1 << 0);
	
	// Red Button              // Second LED
	// GPIOB->IDR & (1 << 6)   // GPIOA->ODR |= (1 << 1);
	
	// Green Button            // Third LED
	// GPIOB->IDR & (1 << 8)   // GPIOA->ODR |= (1 << 4);
	
	// Blue Button             // Fourth LED
	// GPIOB->IDR & (1 << 9)   // GPIOB->ODR |= (1 << 0);

void round_one() {
    // Flash the first LED once
    GPIOA->ODR |= (1 << 0); // Turn on the first LED
    delay();
    GPIOA->ODR &= ~(1 << 0); // Turn off the first LED

    // Wait 3 seconds before showing the first round
    user_delay();

    // Show the first round (First LED)
    GPIOA->ODR |= (1 << 0); // Turn on the first LED to indicate the first round
		delay();
		GPIOA->ODR &= ~(1 << 0);
		delay();
	
    // Wait 10 seconds for user response
    for (int i = 0; i < 10; i++) {
        delay();
        // Check for button press during this time
        if (!(GPIOB->IDR & (1 << 4))) {
            // Turn off all LEDs and display 1 in binary (only the 4th LED on)
            winning_sequence();
						delay();
            GPIOB->ODR |= (1 << 0); // Turn on the 4th LED
						delay();
						delay();
						GPIOB->ODR &= ~(1 << 0);
						delay();
            return; // Exit round_one successfully
        } else if (!(GPIOB->IDR & (1 << 6)) || !(GPIOB->IDR & (1 << 8)) || !(GPIOB->IDR & (1 << 9))) {
            // Any incorrect button pressed
            failure_sequence(); // Trigger ending sequence
            return;
        }
    }

    // If no button is pressed within 2 seconds, trigger the ending sequence
    failure_sequence();
}

#endif