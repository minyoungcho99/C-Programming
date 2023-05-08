.orig x3000
    LD R0, X ; R0 = X
    LD R1, MOD ; R1 = MOD
    NOT R1, R1 
    ADD R1, R1, #1 ; R1 = -MOD
    
WHILE
    ADD R2, R1, R0 ; R2 = X - MOD
    BRn ENDWHILE
    ADD R0, R0, R1 ; X -= MOD
    BR WHILE
ENDWHILE

    ST R0, ANSWER ; mem[ANSWER] = x
    HALT

    X      .fill 17
    MOD    .fill 5     
    ANSWER .blkw 1
.end