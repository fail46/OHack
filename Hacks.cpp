#include "OHack.hpp"

void Hacks::Init ()
{
	WoW::Render = reinterpret_cast<bool (__thiscall*)(unsigned int)>(DetourFunction(reinterpret_cast<byte*>(WoWBase + CGWorldFrame__Render), reinterpret_cast<byte*>(WoW::FrameHook)));
	Misc::SetCommandHook();

	const byte LuaUnlock[] = {0xEB, 0x57};
	Write(WoWBase + CGGameUI__CanPerformAction + 0x20, LuaUnlock, 2);
	Write<byte>(WoWBase + Script_GuildInvite + 0xA2, static_cast<byte>(0xEB));

	// To stop those damn pop-ups
	const byte NoPopups[] = {0x90, 0xE9};
	Write(WoWBase + CGGameUI__ShowBlockedActionFeedback + 0x10, NoPopups, 2);

	Write<byte>(WoWBase + CGCamera__UpdateMotion_ulong_ + 0x238, static_cast<byte>(0xF0));

	const byte NOPs[] = {0x90, 0x90, 0x90, 0x90, 0x90};
	Write(WoWBase + Script_UnitLevel + 0xD3, NOPs, 2);

	Write(WoWBase + CGGameUI__Idle + 0x151, NOPs, 5);
	
	const byte LanguageHack[] = {0xB8, 0x1, 0x0, 0x0, 0x0, 0xC2, 0x08, 0x0};
	Write(WoWBase + IsKnownLanguage, LanguageHack, 8);

	Write(WoWBase + CGUnit_C__SetTrackingTarget + 0x86, NOPs, 5);

	WoW::AddChatMessage("OHack loaded.");
	return;
}

void Hacks::StopFall ()
{
	if(WoW::IsInGame() == false || WoW::GetPlayer() == 0)
	{
		return;
	}

	reinterpret_cast<void (__thiscall*)(unsigned int)>(WoWBase + CMovement_C__Halt)(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement));
	reinterpret_cast<void (__thiscall*)(unsigned int, unsigned int, unsigned int, unsigned int)>(WoWBase + CGUnit_C__OnCollideFallLandNotify)(WoW::GetPlayer(), *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int (__cdecl*)()>(WoWBase + MovementGetGlobals)() + TimestampOffset), *reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement), 1);
	return;
}