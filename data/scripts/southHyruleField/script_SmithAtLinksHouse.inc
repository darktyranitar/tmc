@ Links house Smith
SCRIPT_START script_SmithAtLinksHouse
	BeginBlock
	Call SetPriorityMessage
	Call sub_08066288
	Call sub_08066274
	DoPostScriptAction 0x000a
	SetAnimation 0x000c
	SetAction 0x0003
	EndBlock
script_08009DD2:
	TriggerInteract
	SetAction 0x0002
	Call sub_0806622C
	WaitUntilTextboxCloses
	SetAction 0x0003
	SetAnimation 0x000c
	Jump script_08009DD2
