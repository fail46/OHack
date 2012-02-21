#include "Hack.hpp"

void Hacks::SetNoWater (bool State)
{
	if(State == true)
	{
		Write<byte>(WoWBase + CM2Lighting__SetupGxFog_void_ + 0x22, static_cast<byte>(0xEB));
		const byte NoWater[] = {0x90, 0xE9};
		Write(WoWBase + CWorldView__UpdateViewerLiquid_void_+ 0x19D, NoWater, 2);

		const byte NOPs[] = {0x90, 0x90};
		Write(WoWBase + CGUnit_C__UpdateSwimmingStatus + 0x70, NOPs, 2);

		UI::NoWater->SetChecked(GetNoWater());
	}
	else
	{
		Write<byte>(WoWBase + CM2Lighting__SetupGxFog_void_ + 0x22, static_cast<byte>(0x74));
		const byte NoWater[] = {0x0F, 0x84};
		Write(WoWBase + CWorldView__UpdateViewerLiquid_void_ + 0x19D, NoWater, 2);

		const byte NoSwim[] = {0x75, 0x67};
		Write(WoWBase + CGUnit_C__UpdateSwimmingStatus + 0x70, NoSwim, 2);

		UI::NoWater->SetChecked(GetNoWater());
	}

	return;
}

bool Hacks::GetNoWater ()
{
	return Read<byte>(WoWBase + CM2Lighting__SetupGxFog_void_ + 0x22) == 0xEB;
}