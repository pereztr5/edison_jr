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
	MOVI R3, 31
	MOVI R4, 15	

!loop
	STOR R0, [CURSORX]
	STOR R1, [CURSORY]
	STOR R2, [LEDCOLOR]
	ADD R0, R0, (1)
	ADD R1, R1, (1)

	BRAE R0, R3, [!resetx]
	BRAE R1, R4, [!resety]
    BRA [!loop]

!resetx
	MOVI R0, 0
	BRA [!loop]

!resety
	MOVI R1, 0
	BRA [!loop]

#	BRAE R1, R0, [!label] This jumps if equal to label