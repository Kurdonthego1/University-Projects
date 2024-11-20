#include "stm32f10x.h"
#include "main.h"


//PB4 - D5, Black LED 
	// PA0 - A0
//PB6 - D10, Red LED
	// PA1  - A1
//PB8 - D15, Green LED
	// PA4   - A2
//PB9 - D14, Blue LED
	// PB0  - A3



// Main function


// int main(void) {
int main(void) {
		// Enable clocks for GPIOA, GPIOB, GPIOC
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;
	
		// Setting stuff for STM
		// Pin A4/A1/A0
		GPIOA->CRL = 0x00330033; 
		
		// Pin B6/B4/B0
	  GPIOB->CRL = 0x04040003; 
	
		// Pin B8/9
	  GPIOB->CRH = 0x00000044; 
		
		// Pin C13
		GPIOC->CRH = 0x00400000;
		
		// Phase 2
		for (int i = 0; i < 10; i++)
		{
				GPIOA->ODR |= (1<<5);
				delay();
				GPIOA->ODR &= (0<<5);
				delay();
		}
	
		// While its on
    while (1)
    {
				// Checks if the button connected to PC13 (blue button on the STM) is pressed
				if(!(GPIOC->IDR & (1<<13))) { 	
						GPIOA->ODR |= (1<<5);
				} else if (GPIOC->IDR & (1<<13)) {
						GPIOA->ODR &= (0<<5);
				}
			
        // Check if the button connected to PB4 (black button) is pressed
        // !(GPIOB->IDR & (1 << 4)) checks if PB4 is low (button pressed)
        if (!(GPIOB->IDR & (1 << 4))) {
            GPIOA->ODR |= (1 << 0); // Set PA0 high to turn on LED
        } else if (GPIOB->IDR & (1 << 4)) {
            GPIOA->ODR &= ~(1 << 0); // Clear PA0 to turn off LED
        }

        // Check if the button connected to PB6 (red button) is pressed
        // !(GPIOB->IDR & (1 << 6)) checks if PB6 is low (button pressed)
        if (!(GPIOB->IDR & (1 << 6))) {
            GPIOA->ODR |= (1 << 1); // Set PA1 high to turn on LED
        } else if (GPIOB->IDR & (1 << 6)) {
            GPIOA->ODR &= ~(1 << 1); // Clear PA1 to turn off LED
        }

        // Check if the button connected to PB8 (green button) is pressed
        // !(GPIOB->IDR & (1 << 8)) checks if PB8 is low (button pressed)
        if (!(GPIOB->IDR & (1 << 8))) {
            GPIOA->ODR |= (1 << 4); // Set PA4 high to turn on LED
        } else if (GPIOB->IDR & (1 << 8)) {
            GPIOA->ODR &= ~(1 << 4); // Clear PA4 to turn off LED
        }

        // Check if the button connected to PB9 (blue button) is pressed
        // !(GPIOB->IDR & (1 << 9)) checks if PB9 is low (button pressed)
        if (!(GPIOB->IDR & (1 << 9))) {
            GPIOB->ODR |= (1 << 0); // Set PB0 high to turn on LED
        } else {
            GPIOB->ODR &= ~(1 << 0); // Clear PB0 to turn off LED
        }
    }
	
}
