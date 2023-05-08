
.orig x3000
    HALT

PREORDER_TRAVERSAL
    ADD R6, R6, #-4 ; make space for RV, RA, old FP, and 1 local
	STR R7, R6, #2
	STR R5, R6, #1
	ADD R5, R6, #0
	ADD R6, R6, #-5
	STR R0, R6, #0
	STR R1, R6, #1
	STR R2, R6, #2
	STR R3, R6, #3
	STR R4, R6, #4

TEARDOWN
    LDR R4, R5, #-5
    LDR R3, R5, #-4
    LDR R2, R5, #-3
    LDR R1, R5, #-2
    LDR R0, R5, #-1
    ADD R6, R5, #0
    LDR R7, R5, #2
    LDR R5, R5, #1
    ADD R6, R6, #3
    RET

STACK .fill xF000
.end

.orig x4000    
    .fill 4         
    .fill x4004     
    .fill x4008    
.end

.orig x4004	  
    .fill 2         
    .fill x400C   
    .fill x4010    
.end

.orig x4008	   
    .fill 8       
    .fill 0        
    .fill 0         
.end

.orig x400C 
    .fill 1        
    .fill 0         
    .fill 0         
.end

.orig x4010	   
    .fill 3         
    .fill 0         
    .fill 0         
.end

.orig x4020
    .blkw 5
.end