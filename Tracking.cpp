#include "OHack.hpp"

bool TrackAll = false;
bool TrackObjects = false;
bool TrackPlayers = false;
bool TrackEnemyPlayers = false;
bool TrackEnemies = false;
bool TrackFriendPlayers = false;;
bool TrackFriends = false;
bool TrackNeutral = false;

bool __fastcall CanTrackUnit (unsigned int This, unsigned int, unsigned int ThisObject)
{
	if(TrackAll == true)
	{
		return true;
	}

	if(*reinterpret_cast<unsigned int*>(ThisObject + Type) != ObjectTypes::Unit && *reinterpret_cast<unsigned int*>(ThisObject + Type) != ObjectTypes::Player)
	{
		return false;
	}

	unsigned int Reaction = reinterpret_cast<unsigned int (__thiscall*)(unsigned int, unsigned int)>(WoWBase + CGUnit_C__UnitReaction)(ThisObject, WoW::GetPlayer());
	if(*reinterpret_cast<unsigned int*>(ThisObject + Type) == ObjectTypes::Player)
	{
		if(TrackPlayers == true)
		{
			return true;
		}

		if(Reaction <= 4 && TrackEnemyPlayers == true)
		{
			return true;
		}
		
		if(Reaction >= 5 && TrackFriendPlayers == true)
		{
			return true;
		}
	}

	if(*reinterpret_cast<unsigned int*>(ThisObject + Type) == ObjectTypes::Unit)
	{
		if(Reaction <= 2 && TrackEnemies == true)
		{
			return true;
		}

		if((Reaction == 3 || Reaction == 4) && TrackNeutral == true)
		{
			return true;
		}

		if(Reaction >= 5 && TrackFriends == true)
		{
			return true;
		}
	}

	return reinterpret_cast<bool (__thiscall*)(unsigned int, unsigned int)>(WoWBase + CGPlayer_C__CanTrackUnit)(This, ThisObject);
}

bool __fastcall CanTrackObject (unsigned int This, unsigned int, unsigned int ThisObject)
{
	if(TrackObjects == true)
	{
		return true;
	}

	return reinterpret_cast<bool (__thiscall*)(unsigned int, unsigned int)>(WoWBase + CGPlayer_C__CanTrackObject)(This, ThisObject);
}

void Hacks::Tracking (const char* Track)
{
	if(Read<unsigned int>(WoWBase + TrackingEnumCallback + 0x44C) != reinterpret_cast<unsigned int>(CanTrackUnit) - (WoWBase + TrackingEnumCallback + 0x44C + 0x4))
	{
		Write<unsigned int>(WoWBase + TrackingEnumCallback + 0x44C, reinterpret_cast<unsigned int>(CanTrackUnit) - (WoWBase + TrackingEnumCallback + 0x44C + 0x4));
		Write<unsigned int>(WoWBase + TrackingEnumCallback + 0x44C, reinterpret_cast<unsigned int>(CanTrackUnit) - (WoWBase + TrackingEnumCallback + 0x44C + 0x4));
	}

	static char Message[256];
	ZeroMemory(Message, 256);

	if(_strcmpi(Track, "players") == 0)
	{
		TrackPlayers = !TrackPlayers;
		sprintf_s(Message, "Player tracking %s.", TrackPlayers ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "enemyplayers") == 0)
	{
		TrackEnemyPlayers = !TrackEnemyPlayers;
		sprintf_s(Message, "Enemy player tracking %s.", TrackEnemyPlayers ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "friendlyplayers") == 0)
	{
		TrackFriendPlayers = !TrackFriendPlayers;
		sprintf_s(Message, "Friendly player tracking %s.", TrackFriendPlayers ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "enemies") == 0)
	{
		TrackEnemies = !TrackEnemies;
		sprintf_s(Message, "Enemy unit tracking %s.", TrackEnemies ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "friendly") == 0)
	{
		TrackFriends = !TrackFriends;
		sprintf_s(Message, "Friendly unit tracking %s.", TrackFriends ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "neutral") == 0)
	{
		TrackNeutral = !TrackNeutral;
		sprintf_s(Message, "Neutral unit tracking %s.", TrackNeutral ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "objects") == 0)
	{
		TrackObjects = !TrackObjects;
		sprintf_s(Message, "Object tracking %s.", TrackObjects ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "all") == 0)
	{
		TrackAll = !TrackAll;
		sprintf_s(Message, "Tracking all %s.", TrackAll ? "enabled" : "disabled");
		WoW::AddChatMessage(Message);
		return;
	}

	if(_strcmpi(Track, "off") == 0)
	{
		TrackAll = false;
		TrackObjects = false;
		TrackPlayers = false;
		TrackEnemyPlayers = false;
		TrackFriendPlayers = false;
		TrackEnemies = false;
		TrackFriends = false;
		TrackNeutral = false;
		WoW::AddChatMessage("Tracking disabled.");
		return;
	}

	return;
}