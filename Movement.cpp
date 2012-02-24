#include "OHack.hpp"

void (__thiscall* Hacks::GetMoveStatusReal)(unsigned int, int, int, int);
void __fastcall Hacks::GetMoveStatusHook (unsigned int This, unsigned int, int a1, int a2, int a3)
{
	if(Fly == true)
	{
		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) &= ~MovementFlags::Flying;
	}

	GetMoveStatusReal(This, a1, a2, a3);

	if(Fly == true)
	{
		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) |= MovementFlags::Flying;
	}

	return;
}