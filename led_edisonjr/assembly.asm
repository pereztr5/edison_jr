#Memory addresses

.constant PA  		0x1B1A
.constant PB  		0x1B1B
.constant CURSORX	0x4000
.constant CURSORY	0x4001
.constant LEDCOLOR	0x4002
.constant SSD 		0x4010
.constant READBTN	0x4020
.constant READDIP	0x4030

.address 			0x2000

# R0 : X
# R1 : Y
# R2 : Color
# R3 : MAX X
# R4 : MAX Y

!main
	MOVI R0, 0
	MOVI R1, 0
	MOVI R2, 1
	MOVI R3, 32
	MOVI R4, 16
	MOVI R6, 1
	MOVI R7, 2
	MOVI R8, 4
	MOVI R9, 8

!loop
	LOAD R5, [READBTN]
	
	BRAE R5, R6, [!case1]
    BRAE R5, R7, [!case2]
    BRAE R5, R8, [!case3]
    BRAE R5, R9, [!case4]
    BRA [!loop]

!case1
	MOVI R2, 1
	STOR R2, [LEDCOLOR]
	ADD R1, R1, (1)
	STOR R1, [CURSORY]

	BRA [!loop]

!case2
	MOVI R2, 0
	STOR R2, [LEDCOLOR]
	SUB R1, R1, (1)
	STOR R1, [CURSORY]

	BRA [!loop]

!case3

	MOVI R2, 1
	STOR R2, [LEDCOLOR]
	ADD R0, R0, (1)
	STOR R0, [CURSORX]

	BRA [!loop]

!case4

	MOVI R2, 0
	STOR R2, [LEDCOLOR]
	SUB R0, R0, (1)
	STOR R0, [CURSORX]
	
	BRA [!loop]

