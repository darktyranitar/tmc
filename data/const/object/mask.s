	.include "asm/macros.inc"
	.include "constants/constants.inc"

	.section .rodata
    .align 2

MaskActionFuncs:: @ 081227A4
	.4byte sub_080929A4
	.4byte sub_08092A94
	.4byte sub_08092B0C
	.4byte Mask_Delete+1
