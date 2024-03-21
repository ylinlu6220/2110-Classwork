; Pseudocode

; demo(a, b):
;     if a > b:
;         return a + b
;     else:
;         return abs_diff(a, b)
;
; NOTE: There are coding templates for both caller and callee under Canvas Files > Source Code > Templates
.orig x3000
MAIN
    LD R6, STACK_PTR

    ;; TODO: Push args onto stack for DEMO
    ADD R6, R6, #-1
    LD R0, B
    STR R0, R6, #0

    JSR DEMO
    
    ;; TODO: Pop args and return val from DEMO
    
    HALT

    STACK_PTR .fill xF000
    A   .fill 8
    B   .fill 10


    DEMO 
    ;; TODO: Stack buildup
    
    
    ; if(a - b > 0)
    
    ;; TODO: load args into registers -- R0 with A, R1 with B
    
    
    NOT R2, R1      ; R2 = ~B
    ADD R2, R2, 1   ; R2 = -B
    ADD R2, R0, R2  ; R2 = A-B
    
    BRnz ELSE1
    
    ; return a + b
    
    ;; TODO: calculate result and store appropriately on stack
    
    
    BR ENDIF1
    ELSE1
    ; return abs_diff(a, b)
    
    ;; TODO: push args for ABS_DIFF call
    
    ;; TODO: call ABS_DIFF
    
    ;; TODO: use return value as DEMO's return val
    
    ENDIF1
    
    ;; TODO: Stack teardown 
    
    RET


    ABS_DIFF

        ; Pseudocode

        ; x = a - B
        ; if x < 0:
        ;     return -x
        ; return x

        ADD R6, R6, #-4 ;push 4 words
        STR R7, R6, #2  ;Save the return address --> old R7
        STR R5, R6, #1   ;Save the old frame pointer --> old R5
        ADD R5, R6, #0   ;FP = SP
        ADD R6, R6, #-5 ;push 5 words (going to back up regs now)
        STR R0, R5, #-1 ;save register 0
        STR R1, R5, #-2 ;save register 1
        STR R2, R5, #-3 ;save register 2
        STR R3, R5, #-4 ;save register 3
        STR R4, R5, #-5 ;save register 4


        LDR R0, R5, #4  ; R0 = A (arg1)
        LDR R1, R5, #5  ; R1 = B (arg2)

        NOT R2, R1      ; R2 = ~B
        ADD R2, R2, #1   ; R2 = -B
        ADD R2, R0, R2  ; R2 = A-B

        BRn ELSE2

        STR R2, R5, #3   ; return val = x

        BR ENDIF2

        ELSE2

        NOT R2, R2
        ADD R2, R2, #1
        STR R2, R5, #3

        ENDIF2

        LDR R0, R5, #-1 ;Restore reg 0
        LDR R1, R5, #-2 ;Restore reg 1
        LDR R2, R5, #-3 ;Restore reg 2
        LDR R3, R5, #-4 ;Restore reg 3
        LDR R4, R5, #-5 ;Restore reg 4
        ADD R6, R5, #0   ;Restore SP         sets SP to FP effectively popping registers
        LDR R5, R6, #1   ;Restore FP
        LDR R7, R6, #2   ;Restore RA
        ADD R6, R6, #3   ;Pop RA, FP, LV1

        RET
        
.end