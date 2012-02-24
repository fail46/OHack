#include "OHack.hpp"

int Hacks::SetFlyOnFrame = -1;
int Hacks::SetHoverOnFrame = -1;
unsigned int PlayerAddress = 0;
unsigned int TargetAddress = 0;

bool (__thiscall* WoW::Render)(unsigned int);
bool __fastcall WoW::FrameHook (unsigned int This)
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
	PlayerAddress = reinterpret_cast<unsigned int (__cdecl*)(const char*)>(WoWBase + GetUnitFromName)("Player");
	TargetAddress = reinterpret_cast<unsigned int (__cdecl*)(const char*)>(WoWBase + GetUnitFromName)("Target");
	return Render(This);
}

bool WoW::IsInGame ()
{
	return **reinterpret_cast<byte**>(WoWBase + CGGameUI__EnterWorld + 0xB) == 1;
}

void WoW::AddChatMessage (const char* Message)
{
	reinterpret_cast<void (__cdecl*)(const char*, unsigned int, unsigned int)>(WoWBase + ChatFrame__AddMessage)(Message, 0x25, 0);
	return;
}

unsigned int WoW::GetPlayer ()
{
	return PlayerAddress;
}

unsigned int WoW::GetTarget ()
{
	return TargetAddress;
}

void WoW::DoString (const char* String)
{
	reinterpret_cast<void (__cdecl*)(const char*, const char*, unsigned int)>(WoWBase + FrameScript_ExecuteBuffer)(String, String, 1);
	return;
}