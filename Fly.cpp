#include "OHack.hpp"

bool Hacks::Fly = false;
void Hacks::SetFly (bool State)
{
	if(GetMoveStatusReal == nullptr)
	{
		GetMoveStatusReal = reinterpret_cast<void (__thiscall*)(unsigned int, int, int, int)>(DetourFunction(reinterpret_cast<byte*>(WoWBase + CMovement_C__GetMoveStatus), reinterpret_cast<byte*>(GetMoveStatusHook)));
		if(GetMoveStatusReal == nullptr || *reinterpret_cast<byte*>(WoWBase + CMovement_C__GetMoveStatus) == 0x55)
		{
			throw exception("Unable to hook CMovement_C::GetMoveStatus for fly hack.");
		}
	}

	if(WoW::IsInGame() == false || WoW::GetPlayer() == 0)
	{
		return;
	}

	if(State == true)
	{
		if(*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) & (MovementFlags::Flying | MovementFlags::Swimming) || GetHover() == true)
		{
			return;
		}

		StopFall();

		const byte NoSwim[] = {0x90, 0xE9};
		Write(WoWBase + CGUnit_C__UpdateSwimmingStatus + 0x3C, NoSwim, 2);

		const byte NoJump[] = {0x90, 0x90, 0x83, 0xC4, 0x4};
		Write(WoWBase + Script_JumpOrAscendStart + 0x15D, NoJump, 5);

		Fly = true;

		UI::FlyHack->SetChecked(GetFly());
	}
	else
	{
		const byte NoSwim[] = {0x0F, 0x85};
		Write(WoWBase + CGUnit_C__UpdateSwimmingStatus + 0x3C, NoSwim, 2);

		const byte NoJump[] = {0xE8, 0xE, 0x32, 0x18, 0x0};
		Write(WoWBase + Script_JumpOrAscendStart + 0x15D, NoJump, 5);

		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(WoW::GetPlayer() + CMovement) + 0x38) &= ~MovementFlags::Flying;
		Fly = false;

		UI::FlyHack->SetChecked(GetFly());
	}

	return;
}

bool Hacks::GetFly ()
{
	return Fly;
}