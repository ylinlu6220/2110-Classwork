; Question: check if the first element of the array is less than the last element of the array. If it is, add an element to the array that is the sum of the two
; otherwise add an element to the array that is double the sum of the two
; pseudocode:
;    array = [1, 4, 3, 5]
;    length = 4
;    x = array[0]
;    y = array[length - 1]
;    if x < y:
;       array[length] = x + y
;    else
;    array[length] = 2 * (x + y)

.orig x3000
LD R0, LENGTH           ; R0 = length
LEA R1, ARRAY           ; R1 = address of start of array 
ADD R3, R0, R1          ; R3 = address of arr[length]
LDR R1, R1, #0          ; X = arr[0]
LDR R2, R3, #-1         ; Y = arr[length - 1]

NOT R4, R2              
ADD R5, R1, R4          ; R3 = X-Y
BRn ELSE
ADD R5, R1, R2         ; R5 = X + Y
BR ENDIF
ELSE
ADD R5, R1, R2
ADD R5, R5, R5          ; R5 = 2 (X+Y)
ENDIF
STR R3, R5, 0           ; Store arr[length]
HALT

LENGTH  .FILL 4

ARRAY   .FILL 1
        .FILL 4
        .FILL 3
        .FILL 5
.end