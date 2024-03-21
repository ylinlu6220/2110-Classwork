.orig x0000

AND R1, R1, 0
ADD R1, R1, x0002

AND R2, R2, 0
ADD R2, R2, x0007

AND R7, R7, 0
ADD R7, R7, xffff ; temporarily set the CC to b100

STRMULT R1, R1, R1
STRMULT R2, R2, R2

HALT

.fill x0000
.fill x0000

.end

;; === post-conditions ===
;; R1: x0002, R2: x0007, R7 = xffff, MEM[x0004] = x0020, MEM[x000e] = x0070, CC = b100
