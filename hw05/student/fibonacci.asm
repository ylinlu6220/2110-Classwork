;;=============================================================
;; CS 2110 - Spring 2024
;; Homework 5 - Fibonacci
;;=============================================================
;; Name: Yu Lin Lu
;;=============================================================


;; Suggested Pseudocode (see PDF for explanation)
;;
;; n = mem[N];
;; resAddr = mem[RESULT]
;; 
;; if (n == 1) {
;;     mem[resAddr] = 0;
;; } else if (n > 1) {
;;     mem[resAddr] = 0;
;;     mem[resAddr + 1] = 1;
;;     for (i = 2; i < n; i++) {
;;         x = mem[resAddr + i - 1];
;;         y = mem[resAddr + i - 2];
;;         mem[resAddr + i] = x + y;
;;     }
;; }

.orig x3000
    ;; YOUR CODE HERE
    LD R1, RESULT           ;redAddr = R1 = mem[RESULT]
    LD R0, N                ;n = R0 = mem[N]  n=1 n-1 = 0
    ADD R2, R0, #-1         ;R2 = n-1, if n-1 = 0, n = 1
    BRnp END1
        AND R3, R3, #0      ;R3 = 0
        STR R3, R1, #0      ;stores 0 at mem[resAdder]      
    END1
    ADD R3, R0, #-1         ;R3 = n+1, if n-1 > 0, n > 1
    BRnz END2
        AND R3, R3, #0      ;R3 =0
        STR R3, R1, #0      ;stores 0 at mem[resAdder] 
        ADD R4, R1, #1      ;R4 = resAdder + 1
        ADD R3, R3, #1      ;R3 = 1
        STR R3, R4, #0      ;mem[resAddr + 1] = 1;
        AND R2, R2, #0      ;R2 = i, starts at 2! So just start at 0 then..
        ADD R2, R2, #2      ;ADD 2
        NOT R0, R0          ;R1 = not(n)
        ADD R0, R0, #1      ;R1 = -n
        FOR ADD R3, R2, R0  ;i < n, which is i-n < 0, put this condition in R3
            BRzp END3
            ADD R4, R1, R2  ;R4 = resAdder + i
            ADD R6, R4, #-1 ;R6 = resAdder + i - 1
            ADD R7, R4, #-2 ;R7 = resAdder + i - 2
            LDR R6, R6, #0  ;R6 = mem[R6]
            LDR R7, R7, #0  ;R7 = mem[R7]
            ADD R5, R6, R7  ;R5 = x+y
            STR R5, R4, #0  ;mem[R4] = R5x
            ADD R2, R2, #1  ;incr condition
            BR FOR
        END3
    END2
    HALT

;; Do not rename or remove any existing labels
;; You may change the value of N for debugging
N       .fill 5
RESULT  .fill x4000
.end

.orig x4000
.blkw 100
.end