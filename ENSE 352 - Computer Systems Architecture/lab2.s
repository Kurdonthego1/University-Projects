; Lab2.s source code for program using the ARM Cortex
; Author - Zana Osman
; Created October 2nd, 2024

;;; Directives
	PRESERVE8
	THUMB  
;;; Equates

INITIAL_MSP	EQU		0x20001000	; Initial Main Stack Pointer Value	Allocating 
								              ; 1000 bytes to the stack as it grows down.
			     							    
; Vector Table Mapped to Address 0 at Reset
; Linker requires __Vectors to be exported
	AREA    RESET, DATA, READONLY
	EXPORT  __Vectors

__Vectors	DCD		INITIAL_MSP			; stack pointer value when stack is empty
        	DCD		Reset_Handler		; reset vector
	 		
	ALIGN

; The program
; Linker requires Reset_Handler
	AREA    MYCODE, CODE, READONLY

	ENTRY
	EXPORT	Reset_Handler

	ALIGN
			
Reset_Handler	PROC

; Notice the stack at 0x200000FF8 (Contains R1 then LR ) Little endian
	MOV R0, #0x00001111 ;R0 will now be 0x00001111
	MOV R1, #0x00002222 ;R1 will now be 0x00002222
	MOV R2, #0x00003333 ;R2 will now be 0x00003333
  
	PUSH {R0} ; We push R0 onto the SP and it will now be 11 11 00 00 in the Memory if we watch Address R13
	PUSH {R1} ; Same as R0, now the SP is R1 ^ R0 or 22 22 00 00 11 11 00 00
	PUSH {R2} ; Same as R1, now the SP is R2 ^ R1 ^ R0 or 33 33 00 00 22 22 00 00 11 11 00 00
  
	POP {R3} ; This will pop the value on the SP to R3, so R3 will be 0x00003333 but the SP will only show R1 ^ R0
  
	PUSH{R0, R1, R2} ; Now this pushes all the values back on, the SP will now be R0 ^ R1 ^ R2 ^ R1 ^ R0 so it will have 5 on the stack and it will show on the memory
  
	POP {R0, R1, R2} ; This will pop off the R0 ^ R1 ^ R2 from the SP
	
	

	BL factorial ; Branch to the factorial function


factorial PROC ; factorial function	
	MOV R4, 0x4 ; R4 is the register where we will calculate, using 4 as my integer number
	
	
	
	
	
	BX LR ; Exits the function and goes back to main
ENDP


END