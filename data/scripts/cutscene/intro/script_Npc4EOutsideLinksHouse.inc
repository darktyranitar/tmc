@ NPC4E in front of links house during intro
SCRIPT_START script_Npc4EOutsideLinksHouse
	BeginBlock
	SetEntityPositionRelative 0x0238, 0x01a8
	Call sub_0807F844
	Call SetPriorityMessage
	SetPlayerIdle
	Call sub_0807DF28
	EndBlock
	SetFadeTime 0x0010
	SetFade6
	WaitForFadeFinish
	SetSyncFlag 0x00000001
	WaitForSyncFlagAndClear 0x00000002
	_0807F0B4 0x0004
	CameraTargetPlayer
	Call sub_0807DF50
	EnablePlayerControl
	DoPostScriptAction 0x0006
SCRIPT_END
	.2byte 0x0000
