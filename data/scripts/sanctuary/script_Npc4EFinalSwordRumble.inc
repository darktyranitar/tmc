@ Sanctuary NPC4E Rumble after fusing final sword
SCRIPT_START script_Npc4EFinalSwordRumble
	Call CreatePlayerExclamationMark
	Wait 0x003c
.ifdef EU
	_0807F0B4 0x0007
	SetEntityPositionRelative 0x00e8, 0x00a8
	CameraTargetEntity
	Wait 0x003c
.endif
	SetSyncFlag 0x00000008
	Wait 0x0078
	CallWithArg DeleteRepeatedSoundManager, 0x00000001
	_0807F0C8 0x0000, 0x0000
	Wait 0x003c
	_0807F0B4 0x0004
	SetEntityPositionRelative 0x00e8, 0x0050
	CameraTargetEntity
	Wait 0x003c
	LoadRoomEntityList gUnk_080F55D8
	Wait 0x0078
	_0807F0B4 0x0007
	MoveEntityToPlayer
	CameraTargetEntity
	Wait 0x003c
	EzloMessage TEXT_PANEL_TUTORIAL, 0x02
	WaitUntilTextboxCloses
	_0807F0B4 0x0004
	CameraTargetPlayer
	SetLocalFlag 0x007c
	Call sub_08053250
	Call sub_0807DF50
	EnablePlayerControl
	DoPostScriptAction 0x0006
SCRIPT_END
