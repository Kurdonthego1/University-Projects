;First Program - Zana Osman, Sept 19, 2024

;ARM1.s Source code for my first program on the ARM Cortex M3
;Function Modify some registers so we can observe the results in the debugger
;Author - Dave Duguid
;Modified August 2012 Trevor Douglas
; Directives
  PRESERVE8
  THUMB
		
; Vector Table Mapped to Address 0 at Reset, Linker requires __Vectors to be exported
	AREA RESET, DATA, READONLY
	EXPORT 	__Vectors


__Vectors DCD 0x20002000 ; stack pointer value when stack is empty
	DCD Reset_Handler ; reset vector
	
	ALIGN


;My program, Linker requires Reset_Handler and it must be exported
	AREA MYCODE, CODE, READONLY
	ENTRY

	EXPORT Reset_Handler
		
		
Reset_Handler ;We only have one line of actual application code

label
	LDR R1, = 0x00000001 ; Ry = R1
	LDR R2, = 0x00000002 ; Rz = R2

	ADD R3,R1,R2 ; Add both R1 and R2
	
	LDR R2, = 0xFFFFFFFF
	
	
	ADDS R3,R1,R2  ; Add both R1 and R2 again R3 is now Rz
	
	LDR R2, = 0x2
	
	ADDS R3,R1,R2 
	
	LDR R1, = 0x7FFFFFFF
	LDR R2, = 0x7FFFFFFF
	
	ADDS R3,R1,R2

	b label 

	ALIGN
		
	END

