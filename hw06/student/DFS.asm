;;=============================================================
;;  CS 2110 - Spring 2024
;;  Homework 6 - DFS
;;=============================================================
;;  Name: Yulin lu
;;============================================================

;;  In this file, you must implement the 'SET_VISITED', 'IS_VISITED', and 'DFS' subroutines.


.orig x3000
    ;; You do not need to write anything here
    LD R6, STACK_PTR

    ;; Pushes arguments (address of node 1, target node 5)
    ADD R6, R6, -1
    AND R1, R1, 0
    ADD R1, R1, 5
    STR R1, R6, 0
    ADD R6, R6, -1
    LD R1, STARTING_NODE_ADDRESS
    STR R1, R6, 0
    JSR DFS
    LDR R0, R6, 0
    ADD R6, R6, 3
    HALT

    STACK_PTR .fill xF000
    STARTING_NODE_ADDRESS .fill x6110
    VISITED_VECTOR_ADDR .fill x4199 ;; stores the address of the visited vector.

;;  SET_VISITED Pseudocode

;; Parameter: The address of the node
;; Updates the visited vector to mark the given node as visited

;;  SET_VISITED(addr node) {
;;      visited = mem[mem[VISITED_VECTOR_ADDR]];
;;      data = mem[node];
;;      mask = 1;
;;      while (data > 0) {
;;          mask = mask + mask;
;;          data--;
;;      }
;;      mem[mem[VISITED_VECTOR_ADDR]] = (visited | mask); //Hint: Use DeMorgan's Law!
;;  }

SET_VISITED ;; Do not change this label! Treat this as like the name of the function in a function header
;; Code your implementation for the SET_VISITED subroutine here!
    ;buildup
    ADD R6, R6, #-4
    STR R7, R6, #2
    STR R5, R6, #1
    ADD R5, R6, #0
    ADD R6, R6, #-5
    STR R0, R5, #-1     ;visited
    STR R1, R5, #-2     ;mask
    STR R2, R5, #-3     ;data
    STR R3, R5, #-4     
    STR R4, R5, #-5     ;visited | mask
    
    LDI R0, VISITED_VECTOR_ADDR ;R0 = visited
    AND R1, R1, #0              ;R1 = mask = 1
    ADD R1, R1, #1
    LDR R2, R5, #4              ;R2 = node
    LDR R2, R2, #0              ;R2 = mem[node] = data
    
    WHILE1 BRnz END1
        ADD R1, R1, R1      ;mask = mask + mask
        ADD R2, R2, #-1     ;data --
        BR WHILE1
    END1
    
    ;a or b = not(notA and notB)
    NOT R0, R0
    NOT R1, R1
    AND R4, R0, R1
    NOT R4, R4
    
    STI R4, VISITED_VECTOR_ADDR
    
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


;;  IS_VISITED Pseudocode

;; Parameter: The address of the node
;; Returns: 1 if the node has been visited, 0 if it has not been visited

;;  IS_VISITED(addr node) {
;;       visited = mem[mem[VISITED_VECTOR_ADDR]];
;;       data = mem[node];
;;       mask = 1;
;;       while (data > 0) {
;;           mask = mask + mask;
;;           data--;
;;       }
;;       return (visited & mask) != 0;
;;   }

IS_VISITED ;; Do not change this label! Treat this as like the name of the function in a function header
;; Code your implementation for the IS_VISITED subroutine here!
    ;buildup
    ADD R6, R6, #-4
    STR R7, R6, #2
    STR R5, R6, #1
    ADD R5, R6, #0
    ADD R6, R6, #-5
    STR R0, R5, #-1     ;visited
    STR R1, R5, #-2     ;mask
    STR R2, R5, #-3     ;data
    STR R3, R5, #-4     ;visited & mask
    STR R4, R5, #-5     ;T/F
    
    LDI R0, VISITED_VECTOR_ADDR
    AND R1, R1, #0              ;R1 = mask = 1
    ADD R1, R1, #1
    LDR R2, R5, #4              ;R2 = node
    LDR R2, R2, #0              ;R2 = mem[node] = data
    
    WHILE2 BRnz END2
        ADD R1, R1, R1      ;mask = mask + mask
        ADD R2, R2, #-1     ;data --
        BR WHILE2
    END2
    
    AND R4, R4, #0
    AND R3, R0, R1
    BRnp notZero
        ;is zero -> return 0 (false)
        STR R4, R5, #3
        BR DONE
    notZero ;-> return 1 (true)
        ADD R4, R4, #1
        STR R4, R5, #3
    DONE
    
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



;;  DFS Pseudocode (see PDF for explanation and examples)

;; Parameters: The address of the starting (or current) node, the data of the target node
;; Returns: the address of the node (if the node is found), 0 if the node is not found

;;  DFS(addr node, int target) {
;;        SET_VISITED(node);
;;        if (mem[node] == target) {
;;           return node;
;;        }
;;        result = 0;
;;        for (i = node + 1; mem[i] != 0 && result == 0; i++) {
;;            if (! IS_VISITED(mem[i])) {
;;                result = DFS(mem[i], target);
;;            }
;;        }       
;;        return result;
;;  }

DFS ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the DFS subroutine here!
    ;buildup
    ADD R6, R6, #-4
    STR R7, R6, #2
    STR R5, R6, #1
    ADD R5, R6, #0
    ADD R6, R6, #-5
    STR R0, R5, #-1     ;node -> isVisited(mem[i])
    STR R1, R5, #-2     ;target 
    STR R2, R5, #-3     ;mem[node] -> mem[i]
    STR R3, R5, #-4     ;mem[node] - target -> i = node + 1
    STR R4, R5, #-5     ;result
    
    LDR R0, R5, #4      ;R0 = node
    LDR R1, R5, #5      ;R1 = target
    
    ADD R6, R6, #-1     ;push argument for SET_Visited call
    STR R0, R6, #0
    JSR SET_VISITED
    ADD R6, R6, #1      ;pop the sent in argument
    
    LDR R2, R0, #0      ;R2 = mem[node]
    NOT R3, R1
    ADD R3, R3, #1      ;R3 = -target
    ADD R3, R3, R2      ;R3 = mem[node] - target
    BRnp END3
        STR R0, R5, #3
        BR TEARDOWN
    END3
    
    AND R4, R4, #0      ;R4 = result = 0
    ADD R3, R0, #1      ;R3 = i = node + 1
    ;for (i = node + 1; mem[i] != 0 && result == 0; i++)
    FOR 
        LDR R2, R3, #0      ;R2 = mem[i]
        BRz STOP
        ADD R4, R4, #0
        BRnp STOP
        ;loop starts here
        ADD R6, R6, #-1     ;push mem[i] for VSISTED call
        STR R2, R6, #0
        JSR IS_VISITED
        LDR R0, R6, #0      ;pop the t/f (1/0)
        BRnp END4
            ADD R6, R6, #-2 ;push mem[i], target for recursive call
            STR R1, R6, #1
            STR R2, R6, #0
            JSR DFS
            LDR R4, R6, #0  ;pop out result!
        END4
        ADD R3, R3, #1  ;i++
        BR FOR
    STOP
    
    STR R4, R5, #3
    
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

;; Assuming the graphs starting node (1) is at address x6100, here's how the graph (see below and in the PDF) is represented in memory
;;
;;         0      3
;;          \   / | \
;;            4   1 - 2 
;;             \ /    |
;;              5  -  6
;;

.orig x4199
    .fill 0 ;; visited set will be at address x4199, initialized to 0
.end

.orig x6110         ;; node 1 itself lives here at x6110
    .fill 1         ;; node.data (1)
    .fill x6120     ;; node 2 lives at this address
    .fill x6130     ;; node 3 lives at this address
    .fill x6150     ;; node 5 lives at this address   
    .fill 0
.end

.orig x6120	        ;; node 2 itself lives here at x6120
    .fill 2         ;; node.data (2)
    .fill x6110     ;; node 1 lives at this address
    .fill x6130     ;; node 3 lives at this address
    .fill x6160     ;; node 6 lives at this address
    .fill 0
.end

.orig x6130	        ;; node 3 itself lives here at x6130
    .fill 3         ;; node.data (3)
    .fill x6110     ;; node 1 lives at this address
    .fill x6120     ;; node 2 lives at this address
    .fill x6140     ;; node 4 lives at this address
    .fill 0
.end

.orig x6140	        ;; node 4 itself lives here at x6140
    .fill 4         ;; node.data (4)
    .fill x6100     ;; node 0 lives at this address
    .fill x6130     ;; node 3 lives at this address
    .fill x6150     ;; node 5 lives at this address
    .fill 0
.end

.orig x6100         ;; node 0 itself lives here at x6000
    .fill 0         ;; node.data (0)
    .fill x6140     ;; node 4 lives at this address
    .fill 0
.end

.orig x6150	        ;; node 5 itself lives here at x6150
    .fill 5         ;; node.data (5)
    .fill x6110     ;; node 1 lives at this address
    .fill x6140     ;; node 4 lives at this address
    .fill x6160     ;; node 6 lives at this address
    .fill 0
.end

.orig x6160	        ;; node 6 itself lives here at x6160
    .fill 6         ;; node.data (6)
    .fill x6120     ;; node 2 lives at this address
    .fill x6150     ;; node 5 lives at this address
    .fill 0
.end
 


