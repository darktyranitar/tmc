@ Outro OBJECT_6A Tektite 1
SCRIPT_START script_Object6ATektite1
	BeginBlock
	SetAnimationState 0x0002
	DoPostScriptAction 0x0007
	SetAnimation 0x0000
	EndBlock
	WaitForSyncFlagAndClear 0x00000001
	Call CreateDust
	DoPostScriptAction 0x0006
SCRIPT_END
	.2byte 0x0000
