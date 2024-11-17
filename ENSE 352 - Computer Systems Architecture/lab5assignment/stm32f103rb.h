#ifndef STM32F103RB_H
#define STM32F103RB_H

#include <stdint.h>

typedef struct {
    volatile uint32_t CRL;   // Control Register Low (PA0-PA7)
    volatile uint32_t CRH;   // Control Register High (PA8-PA15)
    volatile uint32_t IDR;   // Input Data Register (PA0-PA15)
    volatile uint32_t ODR;   // Output Data Register (PA0-PA15)
} GPIOA_TypeDef;

typedef struct {
    volatile uint32_t CRL;   // Control Register Low (PA0-PA7)
    volatile uint32_t CRH;   // Control Register High (PA8-PA15)
    volatile uint32_t IDR;   // Input Data Register (PA0-PA15)
    volatile uint32_t ODR;   // Output Data Register (PA0-PA15)
} GPIOB_TypeDef;

typedef struct {
    volatile uint32_t CRL;   // Control Register Low (PA0-PA7)
    volatile uint32_t CRH;   // Control Register High (PA8-PA15)
    volatile uint32_t IDR;   // Input Data Register (PA0-PA15)
    volatile uint32_t ODR;   // Output Data Register (PA0-PA15)
} GPIOC_TypeDef;

typedef struct {
    volatile uint32_t CR;      // Clock control register
    volatile uint32_t CFGR;    // Clock configuration register
    volatile uint32_t CIR;     // Clock interrupt register
    volatile uint32_t APB2RSTR; // APB2 peripheral reset register
    volatile uint32_t APB1RSTR; // APB1 peripheral reset register
    volatile uint32_t AHBENR;   // AHB peripheral clock enable register
    volatile uint32_t APB2ENR;  // APB2 peripheral clock enable register
    volatile uint32_t APB1ENR;  // APB1 peripheral clock enable register
    volatile uint32_t BDCR;     // Backup domain control register
    volatile uint32_t CSR;      // Control/status register
} RCC_TypeDef;

#define GPIOA ((GPIOA_TypeDef*) 0x40010800)
#define GPIOB ((GPIOB_TypeDef*) 0x40010C00)
#define GPIOC ((GPIOC_TypeDef*) 0x40011000)
#define RCC   ((RCC_TypeDef*) 0x40021000)

// Bit definitions for RCC_APB2ENR to enable GPIO ports
#define RCC_APB2ENR_IOPAEN (1 << 2) // Bit 2 for GPIOA clock enable
#define RCC_APB2ENR_IOPBEN (1 << 3) // Bit 3 for GPIOB clock enable
#define RCC_APB2ENR_IOPCEN (1 << 4) // Bit 4 for GPIOC clock enable 

#endif