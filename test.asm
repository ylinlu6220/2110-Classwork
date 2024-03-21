.orig x3000
   AND R3, R3, #0
   ADD R3, R3, #-1
   JSR SUB_RTN
   NOT R3, R3
   HALT
SUB_RTN
   ADD R7, R7, #1
   ADD R3, R3, #2
   RET
.end