#include "OHack.hpp"

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