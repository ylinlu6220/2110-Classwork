; Pseudocode

; demo(a, b):
;     if a > b:
;         return  a + b
;     else:
;         return abs_diff(a, b)

.orig x3000

MAIN 
    LD R6, STACK_PTR

    LD R0, A
    LD R1, B
    
    ; Pushes args onto stack
    ADD R6, R6, #-1 ; Space for b
    STR R1, R6, #0  ; Push b (NOTE: Remember to push arguments on the stack in reverse order)
    
    ADD R6, R6, #-1 ; Space for a
    STR R0, R6, #0  ; Push a 
    
    JSR DEMO
    
    LDR R0, R6, #0 ; Put return value in R0 
    
    ADD R6, R6, #3 ; Pop return value and args
    HALT

STACK_PTR .fill xF000
A   .fill 8
B   .fill 10



DEMO

    ; Callee stack buildup
    
    ADD R6, R6, #-4 ; Push 4 spaces on stack for return value, old R7, old R5, and one local var
    STR R7, R6, #2  ; Save the return address --> old R7
    STR R5, R6, #1  ; Save the old frame pointer --> old R5
    ADD R5, R6, #0  ; FP = SP
    ADD R6, R6, #-5 ; Push 5 spaces (going to back up regs now)
    STR R0, R5, #-1 ; Save register 0
    STR R1, R5, #-2 ; Save register 1
    STR R2, R5, #-3 ; Save register 2
    STR R3, R5, #-4 ; Save register 3
    STR R4, R5, #-5 ; Save register 4

    ; if(a - b > 0)

    ; R0 will be A, R1 will be B
    LDR R0, R5, #4  ; R0 = A (arg1)
    LDR R1, R5, #5  ; R1 = B (arg2)

    NOT R2, R1      ; R2 = ~B
    ADD R2, R2, 1   ; R2 = -B
    ADD R2, R0, R2  ; R2 = A-B

    BRnz ELSE1

    ; return a + b
    
    ADD R3, R0, R1  ; R3 = R0 (A) + R1 (B)
    STR R3, R5, #3
    
    BR ENDIF1

    ELSE1

;   return abs_diff(a, b)

    ; put args on stack

    ADD R6, R6, #-1
    STR R1, R6, 0 ; push b
    ADD R6, R6, #-1
    STR R0, R6, 0 ; push a 

    JSR ABS_DIFF

    LDR R4, R6, #0   ; Put return val from ABS_DIFF in R4
    STR R4, R5, #3   ; Store R4 in return val spot on stack
    ADD R6, R6, #3   ; pop off 2 args and return value from stack

    ENDIF1

    ;; Stack Teardown
    LDR R0, R5, #-1 ; Restore reg 0
    LDR R1, R5, #-2 ; Restore reg 1
    LDR R2, R5, #-3 ; Restore reg 2
    LDR R3, R5, #-4 ; Restore reg 3
    LDR R4, R5, #-5 ; Restore reg 4
    ADD R6, R5, #0  ; Restore SP - sets SP to FP effectively popping registers
    LDR R5, R6, #1  ; Restore FP
    LDR R7, R6, #2  ; Restore RA
    ADD R6, R6, #3  ; Pop RA, FP, LV1

    RET


    ABS_DIFF

        ; Pseudocode

        ; x = a - B
        ; if x < 0:
        ;     return -x
        ; return x

        ADD R6, R6, #-4  ; Push 4 words
        STR R7, R6, #2   ; Save the return address --> old R7
        STR R5, R6, #1   ; Save the old frame pointer --> old R5
        ADD R5, R6, #0   ; FP = SP
        ADD R6, R6, #-5  ; Push 5 words (going to back up regs now)
        STR R0, R5, #-1  ; Save register 0
        STR R1, R5, #-2  ; Save register 1
        STR R2, R5, #-3  ; Save register 2
        STR R3, R5, #-4  ; Save register 3
        STR R4, R5, #-5  ; Save register 4


        LDR R0, R5, #4  ; R0 = A (arg1)
        LDR R1, R5, #5  ; R1 = B (arg2)

        NOT R2, R1      ; R2 = ~B
        ADD R2, R2, 1   ; R2 = -B
        ADD R2, R0, R2  ; R2 = A-B

        BRn ELSE2

        STR R2, R5, 3   ; return val = x

        BR ENDIF2

        ELSE2

        NOT R2, R2
        ADD R2, R2, 1
        STR R2, R5, 3

        ENDIF2

        LDR R0, R5, #-1 ;Restore reg 0
        LDR R1, R5, #-2 ;Restore reg 1
        LDR R2, R5, #-3 ;Restore reg 2
        LDR R3, R5, #-4 ;Restore reg 3
        LDR R4, R5, #-5 ;Restore reg 4
        ADD R6, R5, 0   ;Restore SP         sets SP to FP effectively popping registers
        LDR R5, R6, 1   ;Restore FP
        LDR R7, R6, 2   ;Restore RA
        ADD R6, R6, 3   ;Pop RA, FP, LV1

        RET
        
.end