#include "Hack.hpp"

void Hacks::SetNoCollision (bool State)
{
	if(State == true)
	{
		const byte NoCollision[] = {0x83, 0xC4, 0x10, 0x90, 0x90};
		Write(WoWBase + DoMovementStuff3 + 0x10, NoCollision, 5);
		Write(WoWBase + DoMovementStuff4 + 0xCE, NoCollision, 5);
		Write(WoWBase + DoMovementStuff4 + 0x154, NoCollision, 5);
		UI::NoCollision->SetChecked(GetNoCollision());
	}
	else
	{
		const byte NoCollision1[] = {0xE8, 0x3B, 0xFD, 0xFF, 0xFF};
		const byte NoCollision2[] = {0xE8, 0x1D, 0xBD, 0x0, 0x0};
		const byte NoCollision3[] = {0xE8, 0x97, 0xBC, 0x0, 0x0};
		Write(WoWBase + DoMovementStuff3 + 0x10, NoCollision1, 5);
		Write(WoWBase + DoMovementStuff4 + 0xCE, NoCollision2, 5);
		Write(WoWBase + DoMovementStuff4 + 0x154, NoCollision3, 5);
		UI::NoCollision->SetChecked(GetNoCollision());
	}

	return;
}

bool Hacks::GetNoCollision ()
{
	return Read<byte>(WoWBase + DoMovementStuff3 + 0x10) == 0x83;
}