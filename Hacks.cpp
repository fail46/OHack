#include "Hack.hpp"

int Hacks::SetFlyOnFrame = -1;
int Hacks::SetHoverOnFrame = -1;
unsigned int Hacks::Player;
unsigned int Hacks::Target;

bool (__thiscall* Render)(unsigned int);
bool __fastcall FrameHook (unsigned int This)
{
	if(Hacks::MapID != -1)
	{
		reinterpret_cast<void (__cdecl*)()>(WoWBase + World__UnloadMap)();
		int Unknown = 0;
		reinterpret_cast<int (__cdecl*)(int, int*)>(WoWBase + World__LoadMap)(atoi(UI::MapBox->GetText()), &Unknown);
		Hacks::MapID = -1;
	}

	// Can only toggle the fly and hover hack correctly from the main thread.
	if(Hacks::SetFlyOnFrame != -1)
	{
		Hacks::SetFly(Hacks::SetFlyOnFrame == 1);
		Hacks::SetFlyOnFrame = -1;
	}

	if(Hacks::SetHoverOnFrame != -1)
	{
		Hacks::SetHover(Hacks::SetHoverOnFrame == 1);
		Hacks::SetHoverOnFrame = -1;
	}

	// Have to do this because these functions use TLS, and therefore only work from the main thread.
	Hacks::Player = reinterpret_cast<unsigned int (__cdecl*)(const char*)>(WoWBase + GetUnitFromName)("Player");
	Hacks::Target = reinterpret_cast<unsigned int (__cdecl*)(const char*)>(WoWBase + GetUnitFromName)("Target");
	return Render(This);
}

void Hacks::Init ()
{
	reinterpret_cast<void (__cdecl*)(const char*, unsigned int, unsigned int)>(WoWBase + ChatFrame__AddMessage)("OHack loaded.", 0x25, 0);
	Render = reinterpret_cast<bool (__thiscall*)(unsigned int)>(DetourFunction(reinterpret_cast<byte*>(WoWBase + CGWorldFrame__Render), reinterpret_cast<byte*>(FrameHook)));
	Misc::SetCommandHook();

	const byte LuaUnlock[] = {0xEB, 0x57};
	Write(WoWBase + CGGameUI__CanPerformAction + 0x20, LuaUnlock, 2);
	Write<byte>(WoWBase + Script_GuildInvite + 0xA2, static_cast<byte>(0xEB));

	const byte NOPs[] = {0x90, 0x90, 0x90, 0x90, 0x90};
	Write(WoWBase + Script_UnitLevel + 0xD3, NOPs, 2);

	Write(WoWBase + CGGameUI__Idle + 0x151, NOPs, 5);
	
	const byte LanguageHack[] = {0xB8, 0x1, 0x0, 0x0, 0x0, 0xC2, 0x08, 0x0};
	Write(WoWBase + IsKnownLanguage, LanguageHack, 8);

	Write(WoWBase + CGUnit_C__SetTrackingTarget + 0x86, NOPs, 5);
	return;
}

void Hacks::StopFall ()
{
	if(**reinterpret_cast<byte**>(WoWBase + CGGameUI__EnterWorld + 0xB) != 1 || Player == 0)
	{
		return;
	}

	reinterpret_cast<void (__thiscall*)(unsigned int)>(WoWBase + CMovement_C__Halt)(*reinterpret_cast<unsigned int*>(Player + CMovement));
	reinterpret_cast<void (__thiscall*)(unsigned int, unsigned int, unsigned int, unsigned int)>(WoWBase + CGUnit_C__OnCollideFallLandNotify)(Player, *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int (__cdecl*)()>(WoWBase + MovementGetGlobals)() + TimestampOffset), *reinterpret_cast<unsigned int*>(Player + CMovement), 1);
	return;
}