@ DHC Vaati defeated OBJECT_6A Minish Cap?
SCRIPT_START script_Object6AV3DefeatedMinishCap
	BeginBlock
	SetEntitySpeed 0x0080
	DoPostScriptAction 0x0007
	DoPostScriptAction 0x000b
	SetAnimation 0x0002
	SetEntityPositionRelative 0x00b0, 0x0080
	CallWithArg SetEntityHeight, 0xff800000
	CallWithArg sub_080960C4, script_Object6AV3DefeatedMinishCap2
	EndBlock
	PlaySound SFX_SPARKLES
	_0807EF3C 0xff80, 0x0000
	PlaySound SFX_143
	SetAnimation 0x0004
	SetSyncFlag 0x00000002
	Wait 0x003c
	SetSyncFlag 0x00000004
SCRIPT_END
	.2byte 0x0000
