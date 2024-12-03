#include "stm32f10x.h"
#include "main.h"
#include <stdint.h>

int main(void) {
    // Initialize GPIOs
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

    GPIOA->CRL = 0x00330033; // Configure GPIOA pins as output
    GPIOB->CRL = 0x04040003; // Configure GPIOB pins as input and output
    GPIOB->CRH = 0x00000044; // Configure GPIOB pins for button input
    GPIOC->CRH = 0x00400000; // Configure GPIOC pins (if needed)

        while(1) {
        // Perform the start sequence
    wait_for_user_input();

        // Execute round one
    round_one();
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