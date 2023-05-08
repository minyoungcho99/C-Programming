.orig x3000
AND R0, R0, #0 ; R0 = length

WHILE1 
	LD R7, STRING ; R7 = x4004
	ADD R2, R0, R7 ; R2 = Address of str[length]
	LDR R2, R2, #0; R2 = str[length]
	BRz ENDWHILE1
	
	ADD R0, R0, #1 ; length++
	BR WHILE1
ENDWHILE1

AND R2, R2, #0 ; R2 = left = 0
ADD R3, R0, #-1 ; R3 = right = length - 1

WHILE2
	AND R1, R1, #0
	ADD R1, R1, #1 ; R1 = isPalindrome = 1

	NOT R4, R3
	ADD R4, R4, #1 ; R4 = -right
	ADD R4, R2, R4 ; R4 = left - right
	BRzp ENDWHILE2

	LD R7, STRING
	ADD R7, R7, R2 ; R7 = Address of str[left]
	LDR R5, R7, #0 ; R5 = str[left]

	LD R7, STRING
	ADD R7, R7, R3 ; R7 = Address of str[right]
	LDR R6, R7, #0 ; R6 = str[right]
	
	NOT R6, R6
	ADD R6, R6, #1 ; R6 = -str[right]
	ADD R6, R6, R5 ; R6 = str[left] - str[right]

	BRz ENDIF
		AND R1, R1, #0
		BR ENDWHILE2

	ENDIF
		ADD R2, R2, #1 ; left++
		ADD R3, R3, #-1 ; right--
	BR WHILE2

ENDWHILE2	
 
STI R1, ANSWERADDR
	
HALT

STRING	.fill x4004
ANSWERADDR 	.fill x5005
.end

.orig x4004				   
	.stringz "aibohphobia"
.end

.orig x5005
	ANSWER  .blkw 1
.end