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
	
	BL phase1 ; Branch to the phase 1 function

	BL phase2fact ; Branch to the factorial function

String1
		DCB "ENSE 352 is fun and I am learning ASM assembly!",0
		
String2
		DCB "Yes I really love it!",0
		
	MOV R9, #0x0
	LDR R6, String1
	BL phase3 ; Branch to the phase 3 function
	
	MOV R9, #0x0
	LDR R6, String2
	BL phase3 ; Branch to the phase 3 function
	
phase1 PROC ; phase 1 function
	MOV R0, #0x00001111 ;R0 will now be 0x00001111
	MOV R1, #0x00002222 ;R1 will now be 0x00002222
	MOV R2, #0x00003333 ;R2 will now be 0x00003333
  
	PUSH {R0} ; We push R0 onto the SP and it will now be 11 11 00 00 in the Memory if we watch Address R13
	PUSH {R1} ; Same as R0, now the SP is R1 ^ R0 or 22 22 00 00 11 11 00 00
	PUSH {R2} ; Same as R1, now the SP is R2 ^ R1 ^ R0 or 33 33 00 00 22 22 00 00 11 11 00 00
  
	POP {R3} ; This will pop the value on the SP to R3, so R3 will be 0x00003333 but the SP will only show R1 ^ R0
  
	PUSH{R0, R1, R2} ; Now this pushes all the values back on, the SP will now be R0 ^ R1 ^ R2 ^ R1 ^ R0 so it will have 5 on the stack and it will show on the memory
  
	POP {R0, R1, R2} ; This will pop off the R0 ^ R1 ^ R2 from the SP
	BX LR ; Exits the function and goes back to main
	
ENDP

ALIGN

phase2fact PROC ; factorial function	
	MOV R4, #4 ; R4 is the register where we will calculate, using 4 as my integer number
	MOV R5, #1 ; 1 is always the case we end so we will move into R5
	
	PUSH {R5} ; Push R5 onto the stack pointer
	
p2f_loop
	MUL R4, R5, R4 ; Multiply 
	SUBS R3, #1 ; Subtracts 1 from R3 and allows the function to reduce
	BNE p2f_loop ; Looks for zero flag or when R3 is zero, once it is it will exit the loop
	
	BX LR ; Exits the function and goes back to main
ENDP
	
phase3 PROC
	LDRB R9, [R6], #1
	
	CMP R9, #'A'
	ADDEQ R8, R8, #1
	
	CMP R9, #'a'
	ADDEQ R8, R8, #1
	
	CMP R9, #'E'
	ADDEQ R8, R8, #1
	
	CMP R9, #'e'
	ADDEQ R8, R8, #1

	CMP R9, #'I'
	ADDEQ R8, R8, #1
	
	CMP R9, #'i'
	ADDEQ R8, R8, #1
	
	CMP R9, #'O'
	ADDEQ R8, R8, #1
	
	CMP R9, #'o'
	ADDEQ R8, R8, #1
	
	CMP R9, #'U'
	ADDEQ R8, R8, #1
	
	CMP R9, #'u'
	ADDEQ R8, R8, #1
	
	CMP R9, #'Y'
	ADDEQ R8, R8, #1
	
	CMP R9, #'y'
	ADDEQ R8, R8, #1
	 
	BL phase3 ; Once it hits 0 for R9 it will break out of the function otherwise it will keep going
	
	BX LR ; Exits the function and goes back to main 
ENDP


END