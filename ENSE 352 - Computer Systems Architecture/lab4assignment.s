;;; ENSE 352 LAB 4
;;; Zana Osman 
;;; 200489300
;;; LED on with GPIIO

;;; Equates
end_of_stack	equ 0x20001000			;Allocating 4kB of memory for the stack
RCC_APB2ENR		equ	0x40021018 
RAM_START		equ	0x20000000

GPIOA_CRL 		equ 0x40010800
GPIOC_CRH		equ	0x40011004

GPIOA_ODR		equ 0x4001080C	
GPIOC_IDR		equ 0x40011008	

;;; Vector definitions

	area vector_table, data, readonly
__Vectors
	DCD	0x20002000		; initial stack pointer value
	DCD	Reset_Handler	; program entry point
	export __Vectors

	align

;;; Our mainline code begins here

	area	mainline, code
	entry
	export	Reset_Handler

Reset_Handler proc

	; Call the register configuration function
	BL registerConfig
	
	; Phase 1: Turn the LED on
	BL LED_ON
	
	; Load delay length into r2 (0x8D800) for the blinking LED
	LDR r2, =0x8D800
	
	; Copy the delay length to r3 for restoration after each loop iteration
	MOV r3, r2
	
	; Set the number of LED blinks in r4 (5 times)
	LDR r4, =0x5
	
	; Phase 2: Blink the LED and then turn it off
	BL LED_BLINK
	BL LED_OFF
	
	MOV r9, #0
	LDR r8, =10
	
	; Phase 3: Begin the user input handling loop
	BL userInput
	
	; End of main function, loop indefinitely
doneMain	b	doneMain	; Infinite loop to end main code execution
	endp

	ALIGN
	
; Register configuration function
; Inputs: RCC_APB2ENR, GPIOA_CRL, GPIOC_CRH
; Outputs: Updated register values for enabling ports and configuring pins
	
registerConfig	PROC

	; Load address of RCC_APB2ENR into r6
	LDR r6, = RCC_APB2ENR
	
	; Load the current value of RCC_APB2ENR into r0
	LDR r0, [r6]
	
	; OR mask 0x14 with r0 to enable ports A and C
	ORR r0, #0x14
	
	; Store the new value in RCC_APB2ENR
	STR r0, [r6]
	
	; Configure PA5 as an output pin
	LDR r6, = GPIOA_CRL	; Load GPIOA_CRL address into r6
	LDR r0, [r6]		; Load the current value of GPIOA_CRL into r0
	
	; Set bits 20 and 21 to configure pin 5 as an output
	LDR r1, =0x3
	LSL r1, #20
	ORR r0, r1		

	; Clear bits 22 and 23 to complete output configuration
	LDR r1, =0x3
	LSL r1, #22
	BIC r0, r1
	
	; Store the updated value back into GPIOA_CRL
	STR r0, [r6]
	
	; Configure PC13 as an input pin
	LDR r6, = GPIOC_CRH	; Load GPIOC_CRH address into r6
	LDR r0, [r6]		; Load the current value of GPIOC_CRH into r0
	
	; Clear bits 20 and 21 to configure pin 13 as an input
	LDR r1, =0x3
	LSL r1, #20
	BIC r0, r1
	
	; Set bit 22 to pull-down mode
	LDR r1, =0x1
	LSL r1, #22
	ORR r0, r1
	
	; Clear bit 23 to complete configuration for PC13
	LDR r1, =0x1
	LSL r1, #23
	BIC r0, r1
	
	; Store the updated value back into GPIOC_CRH
	STR r0, [r6]
	
	; Return from function
	BX LR
	ENDP
	
	ALIGN
		
LED_ON		PROC

	; Load GPIOA_ODR address into r6
	LDR r6, = GPIOA_ODR
	
	; Load the current GPIOA_ODR value into r0
	LDR r0, [r6]
	
	; Set bit 5 in r0 to turn on the LED
	LDR r1, =0x1
	LSL r1, #5
	ORR r0, r1

	; Store the new value back into GPIOA_ODR
	STR r0, [r6]
	
	; Return from function
	BX LR
	ENDP
				
	ALIGN
		
LED_OFF		PROC

	; Load GPIOA_ODR address into r6
	LDR r6, = GPIOA_ODR
	
	; Load the current GPIOA_ODR value into r0
	LDR r0, [r6]
	
	; Clear bit 5 in r0 to turn off the LED
	LDR r1, =0x1
	LSL r1, #5
	BIC r0, r1

	; Store the new value back into GPIOA_ODR
	STR r0, [r6]
	
	; Return from function
	BX LR
	ENDP
		
	ALIGN	
	
; Delay function
; Inputs: r2 (current delay count), r3 (original delay count)
; Outputs: None

delay			PROC
	; Compare r2 to 0; if zero, jump to next iteration
	CMP r2, #0
	BEQ nextIteration
	
	; Decrement r2 by 1 to count down delay
	SUB r2, r2, #1
	
	; Loop back to delay if r2 > 0
	B delay
	ENDP
	
	ALIGN
		
nextIteration	PROC

	; Restore r2 to original delay count (stored in r3)
	MOV r2, r3
	
	; Return from function
	BX LR
	ENDP

	ALIGN

; LED blinking function
LED_BLINK PROC

	; Push LR to stack to preserve return address
    push {LR}

blinkLoop

	; Turn LED off and wait for delay
    BL LED_OFF
    BL delay
	
	; Turn LED on and wait for delay
	BL LED_ON
    BL delay
    
    ; Decrement r4 by 1 (counts down blinks)
    SUBS r4, #1
    
	; Repeat blink loop if r4 is not zero
    BNE blinkLoop     

	; Pop LR to restore return address
    pop {LR}
	
	; Return from function
	BX LR
    ENDP

	ALIGN
		
; User input handling
; Inputs: GPIOC_IDR (button state)
; Outputs: Controls LED state via GPIOA_ODR

userInput 	PROC

	; Load GPIOC_IDR address into r6
	LDR r6, = GPIOC_IDR
	
	; Load current GPIOC_IDR value into r0
	LDR r0, [r6]
	
	; Extract bit 13 from GPIOC_IDR to check button state
	LDR r7, =0x1
	LSL r7, #13
	AND r0, r7
	LSR r0, #13

	; Call logicHandler to set LED state based on button
	BL logicHandler
	
	; Loop back to check button state again
	B userInput
	
	BX LR
	ENDP

	ALIGN

; Logic handler for button input
; Inputs: r0 (button state)
; Outputs: Controls LED on/off state

logicHandler 	PROC

	; Compare r0 to 0 (button pressed)
	CMP r0, #0
	
	; If button pressed, turn on LED
	BEQ LED_ON
	
	; If button not pressed, turn off LED
	B LED_OFF
	ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; End of assembly file
	ALIGN
	END
```