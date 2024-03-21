;;=============================================================
;; CS 2110 - Spring 2024
;; Homework 5 - uppercaseInRange 
;;=============================================================
;; Name: 
;;=============================================================

;;  Suggested Pseudocode (see PDF for explanation)
;;  Pseudocode values are based on the labels' default values.
;;
;;  String str = "touppERcase";
;;  int start = mem[START];
;;  int end = mem[END];
;;  int length = mem[LENGTH];
;;  if (end > length) {
;;      end = length;
;;  }
;;
;;  for (int x = start; x < end; x++) {
;;      if (str[x] >= 'a') {
;;          str[x] = str[x] - 32;
;;      }
;;  }


.orig x3000
    LD R7, STRING       ;R7 = str = "touppERcase"
    LD R6, START        ;R6 = start = mem[START]
    LD R5, END          ;R5 = end = mem[END]
    LD R4, LENGTH       ;R4 = length = mem[LENGTH]
    LD R0, LENGTH       ;R0 = length
    NOT R0, R0          
    ADD R0, R0, #1      ;R0 = -length
    ADD R1, R5, R0      ;R1 = end-length 
    BRnz END1           ;(end>length) = (end-length>0)
        LD R5, LENGTH
    END1
    LD R0, START        ;R0 = x = start
    NOT R1, R5          ;R1 = not(end)          
    ADD R1, R1, #1      ;R1 = -end
    FOR ADD R2, R0, R1  ;does x - end < 0?
        BRzp END2
        ADD R5, R7, R0  ;R5 = str[x]
        LDR R3, R5, #0  ;R3 = mem[STR(x)]
        LD R4, ASCII_A  ;R4 = 'a'
        NOT R4, R4
        ADD R4, R4, #1  ;R4 = -'a'
        ADD R4, R3, R4  ;R5 = str[x] - 'a'
        BRn END3
            AND R4, R4, #0  ;R4 = 0
            ADD R4, R4, #-15 ;R4 = -15
            ADD R4, R4, #-15 ;R4 = -30    
            ADD R4, R4, #-2  ;R4 = -32
            ADD R6, R3, R4  ;R6 = str[x] - 32
            STR R6, R5, #0  ;str[x] = R6
        END3
        ADD R0, R0, #1   ;x++
        BR FOR
    END2
    ;; YOUR CODE HERE
    HALT

;; Do not change these values!
STRING          .fill x5000
ASCII_A         .fill 97

;; You can change these numbers for debugging!
LENGTH          .fill 11
START           .fill 2
END             .fill 100

.end

.orig x5000                    ;;  Don't change the .orig statement
    .stringz "touppercase"     ;;  You can change this string for debugging!
.end
