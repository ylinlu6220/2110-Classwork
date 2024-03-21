;;=============================================================
;;  CS 2110 - Spring 2024
;;  Homework 6 - isPalindrome
;;=============================================================
;;  Name: Yulin Lu
;;============================================================

;;  In this file, you must implement the 'isPalindrome' subroutine.
 

.orig x3000
    ;; You do not need to write anything here
    LD R6, STACK_PTR

    ;; Pushes arguments (word addr and len)
    ADD R6, R6, -2
    LEA R0, STRING
    LD R1, LENGTH
    STR R0, R6, 0
    STR R1, R6, 1
    JSR IS_PALINDROME
    LDR R0, R6, 0
    ADD R6, R6, 3
    HALT
    STACK_PTR .fill xF000
    LENGTH .fill 5                 ;; Change this to be length of STRING
    STRING .stringz "rotor"	       ;; You can change this string for debugging!


;;  IS_PALINDROME **RECURSIVE** Pseudocode
;;
;;  isPalindrome(word (addr), len) { 
;;      if (len == 0 || len == 1) {
;;          return 1;
;;      } else {
;;          if (word[0] == word[len - 1]) {
;;              return IS_PALINDROME(word + 1, len - 2);
;;          } else { 
;;              return 0;
;;          }
;;      }
;;  }
;;
IS_PALINDROME ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the isPalindrome subroutine here!
    ;; NOTE: Your implementation MUST be done recursively
    ADD R6, R6, #-4 ;space
    STR R7, R6, #2  ;old addy
    STR R5, R6, #1  ;old frame pointer
    ADD R5, R6, #0  ;local var stack
    ADD R6, R6, #-5 ;space for registers
    STR R0, R6, #4  ;word
    STR R1, R6, #3  ;len
    STR R2, R6, #2  ;1 -> len - 1 
    STR R3, R6, #1  ;word[0] 
    STR R4, R6, #0  ;word[len-1] -> word[0] - word[len-1]
    
    LDR R0, R5, #4  ;R0 = word
    LDR R1, R5, #5  ;R1 = length
    BRz ZERO        ;len = 0, go to 'zero'
    ADD R2, R1, #-1 ;len - 1 = 0 == len = 1, go to 'zero'
    BRz ZERO
    BR ELSE         ;else, go else 
    ZERO                ;return 1
        AND R2, R2, #0
        ADD R2, R2, #1
        STR R2, R5, #3
        BR TEARDOWN
    
    ELSE
        LDR R3, R0, #0  ;word[0]
        ADD R2, R1, #-1 ;R2 = len-1
        ADD R4, R0, R2  
        LDR R4, R4, #0  ;word[len-1]
        NOT R4, R4
        ADD R4, R4, #1  ;-word[len-1]
        ADD R4, R4, R3  ;word[0] - word[len-1]
        BRnp IF
            ADD R0, R0, #1  ;word + 1
            ADD R1, R1, #-2  ;len - 2
            
            ADD R6, R6, #-2 ;push arguments
            STR R0, R6, #0
            STR R1, R6, #1
            JSR IS_PALINDROME
            ;callee teardown
            LDR R0, R6, #0  ;pop + store argument
            STR R0, R5, #3
            BR TEARDOWN
        IF
        ;else
        AND R2, R2, #0
        STR R2, R5, #3
    
    TEARDOWN
    LDR R0, R5, #-1
    LDR R1, R5, #-2
    LDR R2, R5, #-3
    LDR R3, R5, #-4
    LDR R4, R5, #-5
    ADD R6, R5, #0
    LDR R5, R6, #1
    LDR R7, R6, #2
    ADD R6, R6, #3
    RET
.end