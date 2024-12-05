#ifndef MAIN_H
#define MAIN_H

#include "stm32f10x.h"
#include <stdlib.h>    // For rand() and srand()
#include <stdbool.h>   // For bool type

// Definitions
#define MAX_ROUNDS 10
#define NUMBER_OF_LEDS 4

// Function prototypes
void initialize(void);
void startdelay(void);
void delay(void);
bool buttonPress(void);
int buttonSelect(void);
int randomNumberTo4(void);
void starting(void);
void failing(void);
void winning(void);
void wait_for_user_input_and_seed(void);
bool rounds(int round);
void turnOn4LEDs(void);
void turnOff4LEDs(void);

#endif // MAIN_H