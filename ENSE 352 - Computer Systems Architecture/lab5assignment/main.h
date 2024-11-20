// main.h

#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stm32f10x.h>

void delay()
{
    for (int x = 0; x < 1000000; x++) {
        // This loop will create a delay based on your MCU clock speed
    }
}

#endif
