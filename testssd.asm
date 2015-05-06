#Memory addresses

.constant PA  		0x1B1A
.constant PB  		0x1B1B
.constant SSD1 		0x4010
.constant SSD2		0x4011
.constant SSD3 		0x4012
.constant SSD4 		0x4013

.address 			0x2000

!main
    # 0
    MOVI R10, 0x3f
    # 1
    MOVI R11, 0x06
    # 2
    MOVI R12, 0x5b
    # 3
    MOVI R13, 0x4f
    # 4
    MOVI R14, 0x66
    # 5
    MOVI R15, 0x6d
    # 6
    MOVI R16, 0x7d
    # 7
    MOVI R17, 0x07
    # 8
    MOVI R18, 0x7f
    # 9
    MOVI R19, 0x67

    STOR R10, [SSD1]
    STOR R10, [SSD2]
    STOR R10, [SSD3]
!loop
    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R11, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R12, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R13, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R14, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R15, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R16, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R17, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R18, [SSD3]

    STOR R10, [SSD4]
    STOR R11, [SSD4]
    STOR R12, [SSD4]
    STOR R13, [SSD4]
    STOR R14, [SSD4]
    STOR R15, [SSD4]
    STOR R16, [SSD4]
    STOR R17, [SSD4]
    STOR R18, [SSD4]
    STOR R19, [SSD4]
    STOR R10, [SSD4]

    STOR R19, [SSD3]


    BRA [!loop]
