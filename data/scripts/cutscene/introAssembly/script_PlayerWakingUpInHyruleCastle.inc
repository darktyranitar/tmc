@ Intro Hyrule Castle Player Sleeping
SCRIPT_START script_PlayerWakingUpInHyruleCastle
	BeginBlock
	Call sub_0807DF28
	SetPlayerIdle
	SetLocalFlag CASTLE_04_MEZAME
	EndBlock
	Wait 0x003c
	SetFadeTime 0x0004
	SetFade4
	WaitForFadeFinish
script_08009EA4:
	Call CheckAnyKeyPressed
	JumpIfNot script_08009EA4
	DoPostScriptAction 0x0014
	Wait 0x000a
	Call sub_08053250
	EnablePlayerControl
	Call sub_0807DF50
	Call ResetPlayerAnimationAndAction
SCRIPT_END
