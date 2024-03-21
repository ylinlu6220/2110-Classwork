.orig x0000

AND R1, R1, 0
ADD R1, R1, x0002

AND R2, R2, 0
ADD R2, R2, x0007

AND R7, R7, 0
ADD R7, R7, xffff ; temporarily set the CC to b100

LDSKIP MYLABEL

AND R1, R1, 0 ; proper execution jumps over these two lines
AND R7, R7, 0

HALT

MYLABEL .fill x0008 ; (the address that should be skipped past) - should be last AND #

.end

;; === post-conditions ===
;; R1: x0002, R2: x0007, R7 = xffff, CC = b100
