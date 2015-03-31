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

!loop
	MOVI R2, 1
	LOAD R9, [!resetx]
	STOR R9, [!resetx]


	STOR R0, [CURSORX]
	LOAD R9, [!resetx]
	STOR R9, [!resetx]

	STOR R1, [CURSORY]
	LOAD R9, [!resetx]
	STOR R9, [!resetx]
	
	STOR R2, [LEDCOLOR]
	LOAD R9, [!resetx]
	STOR R9, [!resetx]

	ADD R1, R1, (1)
	
	#ADD R0, R0, (1)

	#BRAE R0, R3, [!resetx]
	BRAE R1, R4, [!resety]
    BRA [!loop]



!resety
	MOVI R2, 0

	SUB R1, R1, (1)
	LOAD R9, [!resetx]
	STOR R9, [!resetx]

	STOR R1, [CURSORY]
	LOAD R9, [!resetx]
	STOR R9, [!resetx]
	
	STOR R2, [LEDCOLOR]
	LOAD R9, [!resetx]
	STOR R9, [!resetx]

	BRAE R2, R0, [!loop]
	BRA[!resety]

!resetx
	MOVI R0, 0
	STOR R0, [CURSORX]
	BRA[!loop]
