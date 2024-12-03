;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Project: Lab 3 - Nested subroutine examples
;;; Name: Zana Osman
;;; Student Number: 200489300
;;; File: lab3.s
;;; Class: ENSE 352
;;; Date: Oct, 15, 2024

;;; Directives
	thumb

;;; Equates
end_of_stack	equ 0x20001000			;Allocating 4kB of memory for the stack
RAM_START		equ	0x20000000

;;; Includes
	;; empty

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

;;; Procedure definitions

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

Reset_Handler proc
	;; Copy the string of characters from flash to RAM buffer so it 
	;; can be sorted

	;; Phase 1
	PUSH{LR}
	MOV R0, #0xFFFFFFFF
    BL Bit11
	POP{LR}
	
	; ClearBit function
	PUSH{LR}
    MOV R0, #7
    BL ClearBits
	POP{LR}
	
	; Count 1
	PUSH{LR}
    MOV R0, #6
	MOV R1, #0
    BL Count1
	POP{LR}
	
	;; Phase 2
	PUSH{LR}
	LDR R1, =0x12345678 ; LDR has to have the numbers put in as =0x as opposed to MOV for #0x
	MOV R2, #0x1F ; F tells how many times we shift, 15 and 1 is so we shift right
	MOV R3, #0
	MOV R4, #0
	MOV R5, #0
	MOV R6, #0
	BL rot_left_right1
	POP{LR}

    ;; we are finished
doneMain    b    doneMain        ; finished mainline code.
    endp

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;; Phase 1 ;;

Bit11 PROC
    MOV R2, #2048 ; 2048 is binary for 10 so this will isolate 11 in R2
       
    CMP R3, #0 ; Compare to check if R3 is zero, if its true we go to the 0 bit subroutine
    BEQ IfBit0
IfBit1
    MOV R1, #1 ; If the bit is 1 we can move 1 into R1 and break to main
    BX LR
IfBit0
    MOV R1, #0 ; If the bit is 0 we can move 0 into R1 and break to main
    BX LR

    ENDP

ClearBits PROC
    ORR R0, R0, #0x8 ; Set bit 3 in R0 since 00001000 is 8 as its 2^3
    BIC R0, R0, #0x80 ; BIC is bit clear
    BX LR
    ENDP

Count1 PROC
    MOV R2, #1
    AND R2, R0, R2
    CMP R2, #1
    BEQ Is1

    LSR R0, R0, #1
    CMP R0, #0
    BEQ Done
    B Count1

Is1
    ADD R1, R1, #1
    LSR R0, R0, #1
    CMP R0, #0
    BEQ Done
    B Count1

Done
	BX LR
	
	ENDP

;; Phase 2 ;;
rot_left_right1 PROC
	AND R3, R2, #0x10 ; Check to see if bit 4 is set
	CMP R3, #0x10 ; Compare it to R3, if its set skip the rotate right and branch to rotate left
	BEQ rot_left_left
	
	AND R4, R2, #0xF ; We do this to isolate the lower 4 bits of R2
	LDR R5, =0xFFFF ; Load FFFF to mask the lower 16
	AND R5, R1, R5 ; Do the mask to get the lower 16 bits
	ROR R5, R4 ; Rotate R5
	LDR R6, =0xFFFF0000 ;; Now this is the mask for the upper 16 bits
	AND R6, R1, R6 ; Do the mask to get the upper 16 bits
	ADD R5, R5, R6 ; Then just combine it with the bits that havent been changed
	BX LR
	
rot_left_left
	AND R4, R2, #0xF ; Same
	LDR R5, =0xFFFF ; Same
	AND R5, R1, R5 ; Same
	ADD R4, R4, #0x10 ; This is to add 16 to R4 to get the rotate
	ROR R5, R5, R4 ; Rotate R5 left by R4 which has the 16 addition
	LDR R6, =0xFFFF0000 ; Load in the mask
	AND R6, R1, R6 ; Mask the upper 16 bits
	ADD R5, R5, R6 ; Combine again with the unchanged bits
	BX LR

	ENDP

END                             ; End of assembly file
