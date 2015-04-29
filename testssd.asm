#Memory addresses

.constant PA  		0x1B1A
.constant PB  		0x1B1B
.constant SSD1 		0x4010
.constant SSD2		0x4011
.constant SSD3 		0x4012
.constant SSD4 		0x4013

.address 			0x2000

!main
    #MOVI R2, 0x0
    MOVI R20, 0x8
    MOVI R21, 0x32
!loop
    MOVI R2, 0x1
    STOR R2, [SSD1]
    MOVI R2, 0x0
    STOR R2, [SSD1]

    MOVI R2, 0x1
    STOR R2, [SSD2]
    MOVI R2, 0x0
    STOR R2, [SSD2]

    MOVI R2, 0x1
    STOR R2, [SSD3]
    MOVI R2, 0x0
    STOR R2, [SSD3]
    
    MOVI R2, 0x1
    STOR R2, [SSD4]
!end_loop
    SHL R2, R2, (1)
    STOR R2, [SSD4]
    BRAL R2, R20, [!end_loop]
    MOVI R2, 0x0
    STOR R2, [SSD4]

    MOVI R2, 0x8
    STOR R2, [SSD3]
    MOVI R2, 0x0
    STOR R2, [SSD3]


    MOVI R2, 0x8
    STOR R2, [SSD2]
    MOVI R2, 0x0
    STOR R2, [SSD2]

    MOVI R2, 0x8
    STOR R2, [SSD1]
!start_loop
    SHL R2, R2, (1)
    STOR R2, [SSD1]
    BRAL R2, R21, [!start_loop]
    MOVI R2, 0x0
    STOR R2, [SSD1]

    #ADD R2, R2, (1)
    #MULT R2, R2, (2)
    #SHL R2, R2, (1)
    #BRAG R2, R20, [!main]
    BRA [!loop]
