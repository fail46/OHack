#include "OHack.hpp"

void (__thiscall* Hacks::GetMoveStatusReal)(unsigned int, int, int, int);
void __fastcall Hacks::GetMoveStatusHook (unsigned int This, unsigned int, int a1, int a2, int a3)
{
	if(Fly == true)
	{
		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) &= ~MovementFlags::Flying;
		if(*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) & MovementFlags::Flying)
		{
			Hacks::SetFly(false);
		}
	}

	GetMoveStatusReal(This, a1, a2, a3);

	if(Fly == true)
	{
		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) |= MovementFlags::Flying;
	}

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