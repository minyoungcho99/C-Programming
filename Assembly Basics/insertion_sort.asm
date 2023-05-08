.orig x3000
    HALT

INSERTION_SORT
    ADD R6, R6, #-4  ; make space for RV, RA, old FP, and 1 local
    STR R7, R6, #2   ; save RA
    STR R5, R6, #1   ; save old FP
    ADD R5, R6, #0   ; save FP = SP
    ADD R6, R6, #-5  ; make space for saving registers R0-R4
    STR R0, R6, #-2  ; save R0
    STR R1, R6, #-3  ; save R1
    STR R2, R6, #-4  ; save R2
    STR R3, R6, #-5  ; save R3
    STR R4, R6, #-6  ; save R4

    AND R1, R1, #0
    LDR R1, R5, #5 
    ADD R1, R1, #-1 
    BRnz END 

    STR R1, R6, #1  
    LDR R1, R5, #4 
    STR R1, R6, #0
    JSR INSERTION_SORT
    ADD R6, R6, #3

    LDR R1, R5, #5 
    ADD R1, R1, #-1 
    LDR R0, R5, #4 
    ADD R0, R0, R1 
    LDR R2, R0, #0 
    STR R2, R5, #0 
    ADD R1, R1, #-1 
    STR R1, R5, #-1 

WHILE 
    LDR R1, R5, #-1 
    BRn END_WHILE
    LDR R0, R5, #4 
    ADD R0, R0, R1  
    LDR R3, R0, #0
    LDR R2, R5, #0
    
    NOT R2, R2
    ADD R2, R2, #1
    ADD R2, R3, R2  
    BRnz END_WHILE

    STR R3, R0, #1
    ADD R1, R1, #-1
    STR R1, R5, #-1   
    BR WHILE
  
END_WHILE
    LDR R1, R5, #-1
    LDR R0, R5, #4
    ADD R0, R1, R0 
    ADD R0, R0, #1 
    LDR R2, R5, #0 
    STR R2, R0, #0 
    
END
    LDR R4, R5, #-6 
    LDR R3, R5, #-5 
    LDR R2, R5, #-4 
    LDR R1, R5, #-3 
    LDR R0, R5, #-2 
    ADD R6, R5, #0 
    LDR R7, R5, #2  
    LDR R5, R5, #1  
    ADD R6, R6, #3  
    RET

STACK .fill xF000
.end

.orig x4000
    .fill 2
    .fill 3
    .fill 1
    .fill 1
    .fill 6
.end