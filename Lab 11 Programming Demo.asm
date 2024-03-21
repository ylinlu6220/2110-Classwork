; Products of Adjacent Elements
;
; Given an array of positive integers starting at the label ARRAY, 
; its size at SIZE, and a memory location to store the result at RESULT, 
; find the product of each pair of adjacent elements in the array. 
;
; Example: 
;
; ARRAY = [4, 3, 7, 3, 0, 9]    SIZE = 6    RESULT = x4000
; MEM[x4000] should contain the array [12, 21, 21, 27, 0]
;
; Pseudocode:
;
;   i = 0
;   while (i < size - 1): #size - 1 - i > 
;
;       curr = ARRAY[i]
;       next = ARRAY[i + 1]
;       sum = 0
;
;       while (next > 0):
;           sum += curr
;           next--
;
;       MEM[RESULT + i] = sum
;       i++
;
;
; Extension: How could we accommodate negative numbers?

.orig x3000
    
    ; Write your code here!
    AND R0, R0, #0    ; i(R0) = 0
    LD R1, SIZE     ; R1 = SIZE
    ADD R1, R1, #-1 ; R1 = SIZE - 1
    
    NOT R1, R1
    ADD R1, R2, #1  ; -(SIZE - 1)

WHILE
    ADD R2, R0, R1  ; R2 = placeholder to store output
    BRzp END
    LEA R2, ARRAY   ; R2 = address of array
    ADD R2, R2, R0  ; Addess of array + i
    LDR R3, R2, #0  ; Curr = R3
    
    ADD R2, R2, #1  ; Address of array + i
    LDR R4, R2, #0  ; R4 = next = array + i
    
    AND R5, R5, #0  ; R5 = sum = 0
    
    WHILE2
        ADD R4, R4, #0  ; sets condition code for (next > 0)
        BRnz END2
        ADD R5, R5, R3  ; Sum += curr
        ADD R4, R4, #-1 ; next --
        BR WHILE2
    
    END2
    LD R6, RESULT   ; Load result to R6
    ADD R6, R6, R0  ; RESULT + i
    STR R5, R6, #0  ; Mem[R6] = R5
    ADD R0, R0, #1  ; i ++
END

    HALT
    
    RESULT .fill x4000
    SIZE .fill 6
    
    ARRAY
        .fill 4
        .fill 3
        .fill 7
        .fill 3
        .fill 9
        .fill 0

.end

.orig x4000
    .blkw 5
.end