

.constant PA  0x1B1A
.constant PB  0x1B1B
.constant LED 0x4000
.constant SSD 0x400A
.address 0x2000

!main
	
!loop
	MOVI r1, 10
#	STOR r1, [PA]
	STOR r1, [LED]
	LOAD r2, [LED]
	STOR r2, [PA]
    BRA [!loop]
