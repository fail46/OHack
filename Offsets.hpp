#pragma once

#define CGGameUI__CanPerformAction 0x4D0EC0
#define CGCamera__UpdateMotion 0x03DBC0
#define Script_UnitLevel 0x0543F0
#define CM2Lighting__SetupGxFog_void_ 0x31A760
#define CGUnit__CanSwim 0x626500
#define CWorldView__UpdateViewerLiquid_void_ 0x354470
#define DoMovementStuff1 0x209470
#define DoMovementStuff2 0x209B80
#define DoMovementStuff3 0x331BB0
#define DoMovementStuff4 0x325B10
#define CMovement__SetMovementFlags 0x2051F0
#define CGUnit_C__OnCollideFallLandNotify 0x1B8540
#define GetUnitFromName 0x050AF0
#define IsKnownLanguage 0x165DF0
#define CGGameUI__Idle 0x4DCF60
#define CGUnit_C__SetTrackingTarget 0x1C89A0
#define CGGameUI__EnterWorld 0x4D7C30
#define CGUnit_C__UpdateDisplayInfo 0x1D9AB0
#define World__LoadMap 0x324470
#define World__UnloadMap 0x3257E0
#define CGWorldFrame__Render 0x4E3580
#define CanFlyOrSwim 0x205EB0
#define CGUnit_C__OnCollideFallLandNotify 0x1B8540
#define CMovementShared__StopFalling 0x6204E0
#define MovementGetGlobals 0x1E6B70
#define Script_SendChatMessage 0x4F8710
#define ChatFrame__AddMessage 0x004F5040
#define Script_JumpOrAscendStart 0x04A360
#define CMovement_C__GetMoveStatus 0x171AD0
#define CGUnit_C__UpdateSwimmingStatus 0x1D9DF0
#define CMovement_C__Halt 0x172090
#define Script_GuildInvite 0x4D2D10

#define Descriptors 0xC
#define DisplayID 0xF4
#define OriginalDisplayID 0xF8
#define ObjectScale 0x18
#define CMovement 0x100

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