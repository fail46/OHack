#include "OHack.hpp"

void Hacks::SetClimbHack (bool State)
{
	if(State == true)
	{
		Write<byte>(WoWBase + DoMovementStuff1 + 0x67D, static_cast<byte>(0xEB));

		const byte ClimbHack[] = {0x90, 0x90};
		Write(WoWBase + DoMovementStuff2 + 0x8D8, ClimbHack, 2);

		UI::ClimbHack->SetChecked(GetClimbHack());
	}
	else
	{
		Write<byte>(WoWBase + DoMovementStuff1 + 0x67D, static_cast<byte>(0x74));

		const byte ClimbHack[] = {0x75, 0x0C};
		Write(WoWBase + DoMovementStuff2 + 0x8D8, ClimbHack, 2);

		UI::ClimbHack->SetChecked(GetClimbHack());
	}

	return;
}

bool Hacks::GetClimbHack ()
{
	return Read<byte>(WoWBase + DoMovementStuff1 + 0x67D) == 0xEB;
}