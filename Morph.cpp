#include "Hack.hpp"

int Hacks::MapID = -1;

void Hacks::Morph ()
{
	if(**reinterpret_cast<byte**>(WoWBase + CGGameUI__EnterWorld + 0xB) != 1 || Player == 0)
	{
		return;
	}

	unsigned int Unit = Target ? Target : Player;

	if(strlen(UI::MorphBox->GetText()) != 0)
	{
		*reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(Unit + Descriptors) + DisplayID) = (atoi(UI::MorphBox->GetText()) == 0 ? *reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(Unit + Descriptors) + OriginalDisplayID) : atoi(UI::MorphBox->GetText()));
	}

	if(strlen(UI::ScaleBox->GetText()) != 0 && atof(UI::ScaleBox->GetText()) != 0)
	{
		*reinterpret_cast<float*>(*reinterpret_cast<unsigned int*>(Unit + Descriptors) + ObjectScale) = static_cast<float>(atof(UI::ScaleBox->GetText()));
	}
	
	reinterpret_cast<void (__thiscall*)(unsigned int, unsigned int)>(WoWBase + CGUnit_C__UpdateDisplayInfo)(Unit, 1);
	return;
}

void Hacks::LoadMap ()
{
	if(**reinterpret_cast<byte**>(WoWBase + CGGameUI__EnterWorld + 0xB) != 1 || strlen(UI::MapBox->GetText()) == 0)
	{
		return;
	}

	MapID = atoi(UI::MapBox->GetText());
	return;
}