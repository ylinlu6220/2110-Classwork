;;=============================================================
;; CS 2110 - Spring 2024
;; Homework 5 - palindromeWithSkips
;;=============================================================
;; Name:
;;=============================================================

;;  NOTE: Let's decide to represent "true" as a 1 in memory and "false" as a 0 in memory.
;;
;;  Pseudocode (see PDF for explanation)
;;  Pseudocode values are based on the labels' default values.
;;
;;  String str = "aibohphobia";
;;  char skipChar = mem[mem[CHARADDR]];
;;  int length = 0;
;;  while (str[length] != '\0') {
;;		length++;
;;	}
;; 	
;;	int left = 0;
;;  int right = length - 1;
;;  boolean isPalindrome = true;
;;  while(left < right) {
;;      if (str[left] == skipChar) {
;;          left++;
;;          continue;
;;      }
;;      if (str[right] == skipChar) {
;;          right--;
;;          continue;
;;      }
;;		if (str[left] != str[right]) {
;;			isPalindrome = false;
;;          break;
;;		}
;;
;;		left++;
;;		right--;
;;	}
;;	mem[mem[ANSWERADDR]] = isPalindrome;

.orig x3000
	;; YOUR CODE HERE
	LD R7, STRING           ;R7 = str 
	LDI R6, CHARADDR        ;R6 = skipChar
	AND R5, R5, #0          ;R5 = length = 0
	ADD R4, R7, R5          ;R4 = str[length](location)
	LDR R4, R4, #0          ;R4 = str[length](item)
	WHILE BRz END1
	    ADD R5, R5, #1      ;R5 = Length ++
	    ADD R4, R7, R5      ;R4 = str[length](location)
	    LDR R4, R4, #0      ;R4 = str[length](item)
	    BR WHILE
	END1
	
	AND R4, R4, #0          ;R4 = left = 0
	ADD R3, R5, #-1         ;R3 = right = length - 1
	AND R2, R2, #0          ;R2 = 0
	ADD R2, R2, #1          ;R2 = isPalindrome = 1 (true)
	NOT R1, R3              ;R1 = not(right)
	ADD R1, R1, #1          ;R1 = -right
	ADD R1, R1, R4          ;R1 = left-right
	WHILE1 BRzp END2
	    ADD R0, R7, R4      
	    LDR R0, R0, #0     ;R0 = str[left]
	    NOT R6, R6          
	    ADD R6, R6, #1      ;R6 = -skipchar
	    ADD R1, R0, R6      ;R1 = str[left] - skipchar
	    BRnp END3
	        ADD R4, R4, #1  ;left ++
	    END3
	    ADD R5, R7, R3      
	    LDR R5, R5, #0      ;R5 = str[right]
	    ADD R1, R5, R6      ;R1 = str[right] - skipchar
	    BRnp END4
	        ADD R3, R3, #-1 ;right --
	    END4
	    NOT R1, R5      
	    ADD R1, R1, #1          ;R1 = -str[right]
	    ADD R1, R1, R0          ;R1 = str[left] - str[right]
	    BRz END5
	        AND R2, R2, #0      ;ispalindrome = false (0)
	        BR ENDALL
	    END5
	    ADD R4, R4, #1          ;left++
	    ADD R3, R3, #-1         ;right--
	    NOT R1, R3              ;R1 = not(right)
	    ADD R1, R1, #1          ;R1 = -right
	    ADD R1, R1, R4          ;R1 = left-right
	    BR WHILE1
	END2
	ENDALL
	STI R2, ANSWERADDR      ;PUT ANSWER!!
	HALT

;; Do not change these values!
CHARADDR    .fill x4004
STRING	    .fill x4019
ANSWERADDR 	.fill x5005
.end

;; Do not change any of the .orig lines!

.orig x4004
    .stringz "c"           ;;Feel free to change this char for debugging
.end

.orig x4019				   
	.stringz "raceccar" ;; Feel free to change this string for debugging.
.end

.orig x5005
	ANSWER  .blkw 1        ;;Do not change this value
.end