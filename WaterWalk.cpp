#include "Hack.hpp"

void Hacks::SetWaterWalk (bool State)
{
	if(State == true)
	{
		Write<byte>(WoWBase + CMovement__SetMovementFlags + 0xD, static_cast<byte>(0x11));
		UI::WaterWalk->SetChecked(GetWaterWalk());
	}
	else
	{
		Write<byte>(WoWBase + CMovement__SetMovementFlags + 0xD, static_cast<byte>(0x10));
		UI::WaterWalk->SetChecked(GetWaterWalk());
	}

	return;
}

bool Hacks::GetWaterWalk ()
{
	return Read<byte>(WoWBase + CMovement__SetMovementFlags + 0xD) == 0x11;
}