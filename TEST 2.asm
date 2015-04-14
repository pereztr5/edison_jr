#Memory addresses

.constant PA  		0x1B1A
.constant PB  		0x1B1B
.constant CURSORX	0x4000
.constant CURSORY	0x4001
.constant LEDCOLOR	0x4002
.constant CIRCLE	0x4003
.constant SQUARE	0x4004
.constant SSD 		0x4010
.constant READBTN	0x4020
.constant READDIP	0x4030

.address 			0x2000

# R0 : CANNOT BE CHANGED - ALWAYS 0

# R1 : X
# R2 : Y
# R3 : Color
#
# R15 - R20 : Buttons

!main
	MOVI R1, 0
	MOVI R2, 0
	MOVI R3, 1



	MOVI R15, 1
	MOVI R16, 2
	MOVI R17, 4
	MOVI R18, 8
	MOVI R19, 16
	MOVI R20, 32

!loop
	LOAD R4, [READDIP]
	BRAE R4, R15, [!random]
	BRA [!loop]


!random

	STOR R3, [LEDCOLOR]
	LOAD R4, [READDIP]
	BRAE R4, R0, [!loop]
	BRA [!random]

