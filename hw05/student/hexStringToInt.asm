;;=============================================================
;; CS 2110 - Spring 2024
;; Homework 5 - hexStringToInt
;;=============================================================
;; Name: 
;;=============================================================

;;  Suggested Pseudocode (see PDF for explanation)
;;  Pseudocode values are based on the labels' default values.
;;
;;  String hexString = "F1ED";
;;  int length = mem[LENGTH];
;;  int value = 0;
;;  int i = 0;
;;  while (i < length) {
;;      int leftShifts = 4;
;;      while (leftShifts > 0) {
;;          value += value;
;;          leftShifts--;
;;      }
;;      if (hexString[i] >= 65) {
;;          value += hexString[i] - 55;
;;      } else {
;;          value += hexString[i] - 48;
;;      }
;;      i++;
;;  }
;;  mem[mem[RESULTADDR]] = value;

.orig x3000
    LD R7, HEXSTRING        ;R7 = hexString
    LD R6, LENGTH           ;R6 = length
    AND R5, R5, #0          ;R5 = value = 0
    AND R4, R4, #0          ;R4 = i = 0
    NOT R6, R6              ;R6 = NOT(length)
    ADD R6, R6, #1          ;R6 = -length
    ADD R1, R4, R6          ;R1 = i - length
    WHILE BRzp END1
        AND R3, R3, #0      ;R3 = 0
        ADD R3, R3, #4      ;R3 = 4 (leftshifts)
        WHILE1 BRnz END2
            ADD R5, R5, R5  ;value = value + value
            ADD R3, R3, #-1 ;R3 = leftshifts - 1
            BR WHILE1
        END2
        ADD R2, R7, R4      ;R2 = hexString[i]
        LDR R2, R2, #0      ;R2 = mem[Hextring[i] aka actual value
        LD R0, SIXTYFIVE
        NOT R0, R0
        ADD R0, R0, #1      ;R0 = -65
        ADD R0, R0, R2      ;R3 = hexString - 65
        BRn ELSE
            LD R0, ASCIICHAR
            NOT R0, R0
            ADD R0, R0, #1      ;R0 = -55
            ADD R0, R0, R2 ;R0 = hexString[i] - 55
            ADD R5, R5, R0  ;value = value + hexString[i] - 55
            BR END3
        ELSE 
            LD R0, ASCIIDIG
            NOT R0, R0
            ADD R0, R0, #1      ;R0 = -48
            ADD R0, R0, R2 ;R0 = hexString[i] - 48
            ADD R5, R5, R0  ;value = Value + hexString[i] - 48
        END3
        ADD R4, R4, #1  ;i ++
        ADD R1, R4, R6  ;redo condition
        BR WHILE
    END1
    STI R5, RESULTADDR
    HALT
    
;; Do not change these values!
ASCIIDIG        .fill 48
ASCIICHAR       .fill 55
SIXTYFIVE       .fill 65
HEXSTRING       .fill x5000
LENGTH          .fill 4
RESULTADDR      .fill x4000
.end

.orig x4000                    ;;Don't change the .orig statement
    ANSWER .blkw 1             ;;Do not change this value
.end


.orig x5000                    ;;  Don't change the .orig statement
    .stringz "F1ED"            ;;  You can change this string for debugging! Hex characters will be uppercase.
.end
