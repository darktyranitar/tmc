@ TODO UNUSED?
SCRIPT_START script_08013D44
	BeginBlock
	Call sub_0807F92C
	DoPostScriptAction 0x0008
	CallWithArg sub_0806DA04, 0x00000004
	EndBlock
script_08013D5C:
	CheckEntityInteractType
	JumpIfNot script_08013D5C
	CallWithArg sub_08095D54, 0x00000001
	PlaySound SFX_ELEMENT_PLACE
	SetSyncFlag 0x10000000
	Call SetPlayerActionNormal
	DoPostScriptAction 0x0006
SCRIPT_END
	.2byte 0x0000
