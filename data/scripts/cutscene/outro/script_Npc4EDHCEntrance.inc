@ Outro NPC4E Fix DHC Entrance
SCRIPT_START script_Npc4EDHCEntrance
	BeginBlock
	SetPlayerIdle
	Call sub_0807DF28
	SetEntityPositionRelative 0x0198, 0x01c8
	Call sub_0807F844
	EndBlock
	Wait 0x003c
	PlaySound SFX_EVAPORATE
	CallWithArg sub_0806DA1C, 0x0000000a
	DoPostScriptAction 0x0006
SCRIPT_END
