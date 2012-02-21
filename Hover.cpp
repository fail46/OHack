#include "Hack.hpp"

void Hacks::SetHover (bool State)
{
	if(**reinterpret_cast<byte**>(WoWBase + CGGameUI__EnterWorld + 0xB) != 1 || Player == 0)
	{
		return;
	}

	if(State == true)
	{
		if(*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(Player + CMovement) + 0x38) & (MovementFlags::Flying | MovementFlags::Swimming))
		{
			return;
		}

		StopFall();

		const byte NOPs[] = {0x90, 0x90, 0x90, 0x83, 0xC4, 0x4};
		Write(WoWBase + CanFlyOrSwim + 0x63, NOPs, 3);

		const byte NoSwim1[] = {0x90, 0x90};
		Write(WoWBase + CGUnit__CanSwim + 0x1A, NoSwim1, 2);
		Write<byte>(WoWBase + CGUnit__CanSwim + 0x26, static_cast<byte>(0xEB));

		Write(WoWBase + Script_JumpOrAscendStart + 0x15D, &NOPs[1], 5);

		UI::HoverHack->SetChecked(GetHover());
	}
	else
	{
		const byte Hover[] = {0x33, 0xC0, 0xC3};
		Write(WoWBase + CanFlyOrSwim + 0x63, Hover, 3);

		const byte NoSwim1[] = {0x75, 0x27};
		Write(WoWBase + CGUnit__CanSwim + 0x1A, NoSwim1, 2);
		Write<byte>(WoWBase + CGUnit__CanSwim + 0x26, static_cast<byte>(0x75));

		const byte NoJump[] = {0xE8, 0xE, 0x32, 0x18, 0x0};
		Write(WoWBase + Script_JumpOrAscendStart + 0x15D, NoJump, 5);

		UI::HoverHack->SetChecked(GetHover());
	}

	return;
}

bool Hacks::GetHover ()
{
	return Read<byte>(WoWBase + CanFlyOrSwim + 0x63) == 0x90;
}