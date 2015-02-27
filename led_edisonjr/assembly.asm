

.constant PA  		0x1B1A
.constant PB  		0x1B1B
.constant LED 		0x4000
.constant CURSORX	0x4001
.constant CURSORY	0x4002
.constant SSD 		0x400A
.address 			0x2000

!main
!loop

	MOVI R1, 1
	STOR R1, [LED]

	MOVI R1, 0
	STOR R1, [LED]

	MOVI R1, 1
	STOR R1, [CURSORX]

	MOVI R1, 0
	STOR R1, [CURSORX]

	MOVI R1, 1
	STOR R1, [CURSORY]

	MOVI R1, 0
	STOR R1, [CURSORY]
	    
    BRA [!loop]

#	BRAE R1, R0, [!label] This jumps if equal to label