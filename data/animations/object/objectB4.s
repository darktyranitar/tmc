	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata
    .align 2

gUnk_08124B38:: @ 08124B38
	.incbin "baserom.gba", 0x124B38, 0x0000071

gUnk_08124BA9:: @ 08124BA9
	.incbin "baserom.gba", 0x124BA9, 0x0000053

gUnk_08124BFC:: @ 08124BFC
	.4byte gUnk_08124B38
	.4byte gUnk_08124BA9
	.4byte 00000000
