;;=============================================================
;;  CS 2110 - Spring 2024
;;  Homework 6 - GCD
;;=============================================================
;;  Name: Yulin Lu  
;;============================================================

;;  In this file, you must implement the 'MOD' and 'GCD' subroutines.

.orig x3000
    ;; You do not need to write anything here
    LD R6, STACK_PTR

    ;; Pushes arguments A and B
    ADD R6, R6, -2
    LD R1, A
    STR R1, R6, 0 ; st a at R6
    LD R1, B
    STR R1, R6, 1 ; st b at R6+1
    JSR GCD
    LDR R0, R6, 0
    ADD R6, R6, 3
    HALT

    STACK_PTR   .fill xF000
    ;; You can change these numbers for debugging!
    A           .fill 12
    B           .fill 32


;;  MOD Pseudocode (see PDF for explanation and examples)   
;;  
;;  MOD(int a, int b) {
;;      while (a >= b) {
;;          a -= b;
;;      }
;;      return a;
;;  }

MOD ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the MOD subroutine here!
    ;Stack buildup    
    ADD R6, R6, #-4  ;alocated space for callee buildup
    STR R7, R6, #2   ;store old return address
    STR R5, R6, #1   ;store old frame pointer
    ADD R5, R6, #0   ;FP = SP
    ADD R6, R6, #-5  ;Alocate space for Registers
    STR R0, R5, #-1  ;a
    STR R1, R5, #-2  ;b
    STR R2, R5, #-3  ;
    STR R3, R5, #-4  ;
    STR R4, R5, #-5  ;
    
    LDR R0, R5, #4   ;R0 = a
    LDR R1, R5, #5   ;R1 = b
    
    NOT R2, R1      
    ADD R2, R2, #1   ;R2 = -b 
    ADD R3, R2, R0  ;R3 = a-b (cc)
    WHILE2 BRn END3
        ADD R0, R3, #0   ;a = a-b
        ADD R3, R0, R2  ;r3 = a-b (cc)
        BR WHILE2
    END3
    
    STR R0, R5, #3   ;store return
    
    ;teardown
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


;;  GCD Pseudocode (see PDF for explanation and examples)
;;
;;  GCD(int a, int b) {
;;      if (b == 0) {
;;          return a;
;;      }
;;        
;;      while (b != 0) {
;;          int temp = b;
;;          b = MOD(a, b);
;;          a = temp;
;;      }
;;      return a;
;;  }

GCD ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the GCD subroutine here!

    ;Stack buildup    
    ADD R6, R6, #-4  ;alocated space for callee buildup
    STR R7, R6, #2   ;store old return address
    STR R5, R6, #1   ;store old frame pointer
    ADD R5, R6, #0   ;FP = SP
    ADD R6, R6, #-5  ;Alocate space for Registers
    STR R0, R5, #-1  ;a
    STR R1, R5, #-2  ;b
    STR R2, R5, #-3  ;temp
    STR R3, R5, #-4  ;
    STR R4, R5, #-5  ;
    
    LDR R0, R5, #4   ;R0 = a
    LDR R1, R5, #5   ;R1 = b
    
    BRnp END1
        STR R0, R5, #3 ;set return to a
        BR TEARDOWN
    END1
    
    STR R0, R6, #0
    STR R1, R6, #1
    WHILE1 BRz END2
        ADD R2, R1, #0 ;R2 = temp = b
        
        ;caller for MOD
        ADD R6, R6, #-2
        STR R1, R6, #1   ;push b
        STR R0, R6, #0   ;push a
        JSR MOD
        
        LDR R1, R6, #0   ;pop return
        ADD R6, R6, #3   ;pop arguments(2) + return
        
        ADD R0, R2, #0   ;a = temp
        ADD R1, R1, #0   ;cc b
        BR WHILE1       
    END2
    
    STR R0, R5, #3
    
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