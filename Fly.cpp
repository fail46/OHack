#include "OHack.hpp"

__declspec(naked) void __fastcall CalcDirectionHook ()
{
	static unsigned int This = 0;
	__asm
	{
		mov This, ecx
	}

	get<unsigned int>(get<unsigned int>(WoW::GetPlayer() + CMovement) + 0x38) |= MovementFlags::Flying;
	reinterpret_cast<void (__thiscall*)(unsigned int)>(WoWBase + CMovement__CalcDirection)(This);
	get<unsigned int>(get<unsigned int>(WoW::GetPlayer() + CMovement) + 0x38) &= ~MovementFlags::Flying;

	__asm
	{
		retn
	}
}

void Hacks::SetFly (bool State)
{
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

		const byte NOPs[] = {0x90, 0x90, 0x90, 0x83, 0xC4, 0x4};
		Write(WoWBase + CanFlyOrSwim + 0x63, NOPs, 3);

		const byte NoSwim[] = {0x90, 0xE9};
		Write(WoWBase + CGUnit_C__UpdateSwimmingStatus + 0x3C, NoSwim, 2);

		const byte NoJump[] = {0x90, 0x90, 0x83, 0xC4, 0x4};
		Write(WoWBase + Script_JumpOrAscendStart + 0x15D, NoJump, 5);

		Write<signed int>(WoWBase + CMovementShared__CalcDirection + 0x1A, reinterpret_cast<unsigned int>(CalcDirectionHook) - (WoWBase + CMovementShared__CalcDirection + 0x1E));

		UI::FlyHack->SetChecked(GetFly());
	}
	else
	{
		const byte Fly1[] = {0x33, 0xC0, 0xC3};
		Write(WoWBase + CanFlyOrSwim + 0x63, Fly1, 3);

		const byte NoSwim[] = {0x0F, 0x85};
		Write(WoWBase + CGUnit_C__UpdateSwimmingStatus + 0x3C, NoSwim, 2);

		byte NoJump[] = {0xE8, 0x0, 0x0, 0x0, 0x0};
		get<unsigned int>(&NoJump[1]) = (WoWBase + SendJump) - (WoWBase + Script_JumpOrAscendStart + 0x15E + 0x4);
		Write(WoWBase + Script_JumpOrAscendStart + 0x15D, NoJump, 5);

		Write<signed int>(WoWBase + CMovementShared__CalcDirection + 0x1A, (WoWBase + CMovement__CalcDirection) - (WoWBase + CMovementShared__CalcDirection + 0x1E));

		UI::FlyHack->SetChecked(GetFly());
	}

	return;
}

bool Hacks::GetFly ()
{
	return Read<signed int>(WoWBase + CMovementShared__CalcDirection + 0x1A) == (reinterpret_cast<unsigned int>(CalcDirectionHook) - (WoWBase + CMovementShared__CalcDirection + 0x1E));
}