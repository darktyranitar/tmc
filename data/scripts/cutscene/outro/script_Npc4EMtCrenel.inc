@ Outro NPC4E Mt. Crenel
SCRIPT_START script_Npc4EMtCrenel
	BeginBlock
	SetPlayerIdle
	Call sub_0807DF28
	SetEntityPositionRelative 0x0128, 0x0058
	Call sub_0807F844
	EndBlock
	Wait 0x003c
	SetSyncFlag 0x00000001
	Wait 0x000a
	SetSyncFlag 0x00000002
	Wait 0x0014
	SetSyncFlag 0x00000004
	Wait 0x001e
	SetSyncFlag 0x00000008
	Wait 0x003c
	CallWithArg sub_0806DA1C, 0x0000000e
	DoPostScriptAction 0x0006
SCRIPT_END
