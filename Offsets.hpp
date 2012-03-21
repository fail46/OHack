#pragma once

#define CGGameUI__CanPerformAction 0x4D0B80
#define Script_UnitLevel 0x054420
#define CM2Lighting__SetupGxFog_void_ 0x319E80
#define CGUnit__CanSwim 0x6258F0
#define CWorldView__UpdateViewerLiquid_void_ 0x353BF0
#define DoMovementStuff1 0x208FD0
#define DoMovementStuff2 0x2096E0
#define DoMovementStuff3 0x331290
#define DoMovementStuff4 0x3251F0
#define CMovement__SetMovementFlags 0x204D50
#define CGUnit_C__OnCollideFallLandNotify 0x1B8140
#define GetUnitFromName 0x050B20
#define IsKnownLanguage 0x165B70
#define CGGameUI__Idle 0x4DCC30
#define CGUnit_C__SetTrackingTarget 0x1C85B0
#define CGGameUI__EnterWorld 0x4D7900
#define CGUnit_C__UpdateDisplayInfo 0x1D9650
#define World__LoadMap 0x323B30
#define World__UnloadMap 0x324EA0
#define CGWorldFrame__Render 0x4E3400
#define CanFlyOrSwim 0x205A10
#define CMovementShared__StopFalling 0x61F8D0
#define MovementGetGlobals 0x1E65E0
#define Script_SendChatMessage 0x4F8140
#define ChatFrame__AddMessage 0x004F4A70
#define Script_JumpOrAscendStart 0x04A390
#define CMovement_C__GetMoveStatus 0x171610
#define CGUnit_C__UpdateSwimmingStatus 0x1D9990
#define CMovement_C__Halt 0x171C00
#define Script_GuildInvite 0x4D29C0
#define CGGameUI__ShowBlockedActionFeedback 0x4C9640
#define CGCamera__UpdateMotion_ulong_ 0x03DBF0
#define FrameScript_ExecuteBuffer 0x43A810
#define CGUnit_C__UnitReaction 0x1BE660
#define TrackingEnumCallback 0x5D1550
#define CGPlayer_C__CanTrackUnit 0x161A40
#define CGPlayer_C__CanTrackObject 0x161AD0
#define CMovementShared__CalcDirection 0x61F1A0
#define CMovement__CalcDirection 0x61DB60
#define SendJump 0x1CD2D0
#define ObfuscateLanguage 0x4EB7D0
#define CGUnit_C__GetCreatureRank 0x1AF990
#define SomeLuaFunction 0x02B170

#define Descriptors 0xC
#define DisplayID 0xF4
#define OriginalDisplayID 0xF8
#define ObjectScale 0x18
#define CMovement 0x100
#define Type 0x14

#define TimestampOffset 0x128

enum MovementFlags
{
	StunnedOrRooted = 0x400,
	Falling = 0x800,
	FallingFar = 0x1000,
	Swimming = 0x100000,
	Flying = 0x1000000,
	Mounted = 0x10000000,
};

enum ObjectTypes
{
	Object = 0,
	Item = 1,
	Container = 2,
	Unit = 3,
	Player = 4,
	GameObject = 5,
	DynamicObject = 6,
	Corpse = 7,
	AiGroup = 8,
	AreaTrigger = 9,
};