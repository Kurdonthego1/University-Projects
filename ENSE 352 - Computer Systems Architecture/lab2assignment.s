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
	
	BL phase1 ; Branch to the phase 1 function, LR should update when we branch in

	BL phase2fact ; Branch to the factorial function
		
	LDR R7, = string1
	BL countVowels ; Branch to the phase 3 function
	
	LDR R7, = string2
	BL countVowels ; Branch to the phase 3 function
	
	ENDP
	
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
	MOV R4, #0 ; R4 is the register where we will calculate, using 4 as my integer number
	MOV R5, #1 ; 1 is always the case we end so we will move into R5
	
	PUSH {R5} ; Push R5 onto the stack pointer
	
p2f_loop
	CMP R4, #0
	BEQ zero
loop1
 	MUL R5, R4, R5 ; Multiply 
	SUBS R4, #1 ; Subtracts 1 from R3 and allows the function to reduce
	B loop1

	BNE p2f_loop ; Looks for zero flag or when R3 is zero, once it is it will exit the loop

zero	 
	MOV R4, #0
	
	BX LR ; Exits the function and goes back to main
	ENDP
	
string1
	DCB "ENSE 352 is fun and I am learning ASM assembly!", 0
		
string2
	DCB "Yes I really love it!", 0
	
	
countVowels PROC
	PUSH {R9, LR}
	MOV R8, #0 ; Initialize counter to 0
	
loop 
	LDRB R9, [R7] ; Load in one byte of the string to be used to compare
	
	CMP R9, #'A' ; Compare against 'A' if it is similar add 1 to the count, same for all CMP
	ADDEQ R8, R8, #1 ; Adds one to the count if the CMP function goes, if not it does not add, same for all ADDEQ
	
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
	
	ADD R7, R7, #1
	CMP R0, #0
	BNE loop
	; Once it hits 0 for R9 it will break out of the function otherwise it will keep going
	POP {R0, LR}

	BX LR ; Exits the function and goes back to main 
	ENDP


	END