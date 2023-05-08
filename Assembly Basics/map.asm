.orig x3000
HALT

STACK .fill xF000

MAX
;; Stack Buildup
ADD R6, R6, #-4
STR R7, R6, #2
STR R5, R6, #1
ADD R5, R6, #0
ADD R6, R6, #-7
STR R0, R6, #4
STR R1, R6, #3 
STR R2, R6, #2 
STR R3, R6, #1 
STR R4, R6, #0 

;; Store params
LDR R0, R5, #4 ; R0 = a
LDR R1, R5, #5 ; R1 = b

NOT R1, R1
ADD R1, R1, #1 ; R1 = -b

;; IF/ELSE
IF
ADD R0, R0, R1 ; R0 = a - b
BRnz ELSE
AND R0, R0, #0
STR R0, R5, #3 ; return 0
BR TEARDOWN1

ELSE
AND R0, R0, #0
ADD R0, R0, #1
STR R0, R5, #3 ; return 1
BR TEARDOWN1

;; Stack Teardown
TEARDOWN1
LDR R4, R6, #0
LDR R3, R6, #1
LDR R2, R6, #2
LDR R1, R6, #3
LDR R0, R6, #4
ADD R6, R5, #0
LDR R5, R6, #1
LDR R7, R6, #2
ADD R6, R6, #3
RET

DIV
;; Stack Buildup
ADD R6, R6, #-4
STR R7, R6, #2
STR R5, R6, #1
ADD R5, R6, #0
ADD R6, R6, #-7
STR R0, R6, #4
STR R1, R6, #3 
STR R2, R6, #2
STR R3, R6, #1
STR R4, R6, #0

;; IF/ELSE
IF2
;; Store params
LDR R0, R5, #4 ; R0 = x
LDR R1, R5, #5 ; R1 = y

NOT R0, R0
ADD R0, R0, #1 ; R0 = -x
ADD R0, R0, R1 ; R0 = y - x
BRnz ELSE2
AND R0, R0, #0
STR R0, R5, #3 ; return 0
BR TEARDOWN2

ELSE2
ADD R6, R6, #-2 ; for DIV(x - y, y)
LDR R0, R5, #4 ; R0 = x
LDR R1, R5, #5 ; R1 = y

NOT R1, R1
ADD R1, R1, #1 ; R1 = -y

ADD R0, R1, R0 ; R0 = x - y
STR R0, R6, #0 ; store x - y on the top of stack

LDR R0, R5, #5 ; R0 = y
STR R0, R6, #1 ; store y on the top of stack
JSR DIV
LDR R0, R6, #0
ADD R0, R0, #1

ADD R6, R6, #3

STR R0, R5, #3 ; return 1 + DIV(x - y, y)
BR TEARDOWN2

;; Stack Teardown
TEARDOWN2
LDR R4, R6, #0
LDR R3, R6, #1
LDR R2, R6, #2
LDR R1, R6, #3
LDR R0, R6, #4
ADD R6, R5, #0
LDR R5, R6, #1
LDR R7, R6, #2
ADD R6, R6, #3
RET


MAP
;; Stack Buildup
ADD R6, R6, #-4
STR R7, R6, #2
STR R5, R6, #1
ADD R5, R6, #0
ADD R6, R6, #-10 ; 5 LVs
STR R0, R6, #4
STR R1, R6, #3
STR R2, R6, #2
STR R3, R6, #1
STR R4, R6, #0

AND R0, R0, #0
STR R0, R5, #0 ; i = 0
WHILE
LDR R0, R5, #0 ; R0 = i
LDR R1, R5, #5 ; R1 = length

NOT R1, R1
ADD R1, R1, #1 ; R1 = -length

ADD R0, R0, R1 ; R0 = i - length
BRzp TEARDOWN3

;; int firstElem = arr[i]
LDR R0, R5, #4 ; R0 = arr
LDR R1, R5, #0 ; R1 = i
ADD R0, R0, R1 ; R0 = address of arr[i]
LDR R0, R0, #0 ; R0 = arr[i]
STR R0, R5, #-1 ; firstElem = arr[i]

;; int secondElem = arr[i + 1]
LDR R0, R5, #4 ; R0 = arr
LDR R1, R5, #0 ; R1 = i
ADD R1, R1, #1 ; R1 = i + 1
ADD R0, R0, R1 ; R0 = address of arr[i + 1]
LDR R0, R0, #0 ; R0 = arr[i + 1]
STR R0, R5, #-2 ; secondElem = arr[i + 1]

;; int div = DIV(firstElem, secondElem)
ADD R6, R6, #-2 ; for DIV(firstElem, secondElem)
LDR R0, R5, #-1 ; R0 = firstElem
STR R0, R6, #0 ; store firstElem on the top of stack

LDR R0, R5, #-2 ; R0 = secondElem
STR R0, R6, #1 ; store secondElem on the top of stack
JSR DIV
LDR R0, R6, #0
ADD R6, R6, #3
STR R0, R5, #-3 ; div = DIV(firstElem, secondElem)

;; int offset = MAX(firstElem, secondElem);
ADD R6, R6, #-2 ; for MAX(firstElem, secondElem)
LDR R0, R5, #-1 ; R0 = firstElem
STR R0, R6, #0 ; store firstElem on the top of stack

LDR R0, R5, #-2 ; R0 = secondElem
STR R0, R6, #1 ; store secondElem on the top of stack
JSR MAX
LDR R0, R6, #0
ADD R6, R6, #3
STR R0, R5, #-4 ; offset = MAX(firstElem, secondElem)

;; arr[i + offset] = div
LDR R0, R5, #0 ; R0 = i
LDR R1, R5, #-4 ; R1 = offset
ADD R0, R0, R1 ; R0 = i + offset

LDR R1, R5, #4 ; R1 = arr
ADD R0, R0, R1 ; R0 = address of arr[i + offset]
LDR R1, R5, #-3 ; R1 = div
STR R1, R0, #0 ; arr[i + offset] = div

;; i += 2
LDR R0, R5, #0 ; R0 = i
ADD R0, R0, #2 ; i += 2
STR R0, R5, #0 

BR WHILE

;; Stack Teardown
TEARDOWN3
LDR R4, R6, #0
LDR R3, R6, #1
LDR R2, R6, #2
LDR R1, R6, #3
LDR R0, R6, #4
ADD R6, R5, #0
LDR R5, R6, #1
LDR R7, R6, #2
ADD R6, R6, #3
RET

LENGTH .fill x12

ARRAY .fill x4000

.end

.orig x4000
.fill 12
.fill 3
.fill 5
.fill 7
.fill 16
.fill 2
.fill 5
.fill 5
.fill 25
.fill 7
.fill 48
.fill 60
.end