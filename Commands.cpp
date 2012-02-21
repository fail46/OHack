#include "Hack.hpp"

#pragma warning (disable : 4996)

char* Command = nullptr;

inline void AddChat (const char* Message)
{
	reinterpret_cast<void (__cdecl*)(const char*, unsigned int, unsigned int)>(WoWBase + ChatFrame__AddMessage)(Message, 0x25, 0);
}

bool HandleCommand ()
{
	try
	{
		if(strcmpi(Command, ".nowater") == 0)
		{
			if(UI::NoWater->IsChecked() == false)
			{
				Hacks::SetNoWater(true);
				AddChat("No Water hack enabled.");
			}
			else
			{
				Hacks::SetNoWater(false);
				AddChat("No Water hack disabled.");
			}
		}
		else if(strcmpi(Command, ".climb") == 0)
		{
			if(UI::ClimbHack->IsChecked() == false)
			{
				Hacks::SetClimbHack(true);
				AddChat("Climb hack enabled.");
			}
			else
			{
				Hacks::SetClimbHack(false);
				AddChat("Climb hack disabled.");
			}
		}
		else if(strcmpi(Command, ".hover") == 0)
		{
			if(UI::HoverHack->IsChecked() == false)
			{
				Hacks::SetHover(true);
				if(Hacks::GetHover() == true)
				{
					AddChat("Hover hack enabled.");
				}
				else
				{
					AddChat("The hover hack can't be enabled while flying or swimming.");
				}
			}
			else
			{
				Hacks::SetHover(false);
				AddChat("Hover hack disabled.");
			}
		}
		else if(strcmpi(Command, ".fly") == 0)
		{
			if(UI::FlyHack->IsChecked() == false)
			{
				Hacks::SetFly(true);
				if(Hacks::GetFly() == true)
				{
					AddChat("Fly hack enabled.");
				}
				else
				{
					AddChat("The fly hack can't be enabled while flying, hovering, or swimming.");
				}
			}
			else
			{
				Hacks::SetFly(false);
				AddChat("Fly hack disabled.");
			}
		}
		else if(strcmpi(Command, ".nocollision") == 0 || strcmpi(Command, ".noclip") == 0)
		{
			if(UI::NoCollision->IsChecked() == false)
			{
				Hacks::SetNoCollision(true);
				AddChat("No Collision hack enabled.");
			}
			else
			{
				Hacks::SetNoCollision(false);
				AddChat("No Collision hack disabled.");
			}
		}
		else if(strcmpi(Command, ".waterwalk") == 0)
		{
			if(UI::WaterWalk->IsChecked() == false)
			{
				Hacks::SetWaterWalk(true);
				AddChat("Water Walk hack enabled.");
			}
			else
			{
				Hacks::SetWaterWalk(false);
				AddChat("Water Walk hack disabled.");
			}
		}
		else if(strcmpi(Command, ".stopfall") == 0)
		{
			Hacks::StopFall();
		}
		else if(std::string(Command).find(".morph") != std::string::npos)
		{
			const char* Previous = UI::MorphBox->GetText();
			char* ModelID = new char[6];
			ZeroMemory(ModelID, 6);
			memcpy(ModelID, &Command[7], 5);
			UI::MorphBox->SetText(ModelID);
		
			char* String = new char[100];
			sprintf(String, "%s morphed to display ID: %s", Hacks::Target == 0 ? "Player" : "Target", ModelID);
			AddChat(String);
			delete[] String;

			delete[] ModelID;
			Hacks::Morph();
			UI::MorphBox->SetText(Previous);
		}
		else if(std::string(Command).find(".scale") != std::string::npos)
		{
			const char* Previous = UI::ScaleBox->GetText();
			char* Scale = new char[6];
			ZeroMemory(Scale, 6);
			memcpy(Scale, &Command[7], 5);
			UI::ScaleBox->SetText(Scale);

			char* String = new char[100];
			sprintf(String, "%s scale set to: %s", Hacks::Target == 0 ? "Player" : "Target", Scale);
			AddChat(String);
			delete[] String;

			delete[] Scale;
			Hacks::Morph();
			UI::ScaleBox->SetText(Previous);
		}
		else if(std::string(Command).find(".loadmap") != std::string::npos)
		{
			const char* Previous = UI::MapBox->GetText();
			char* Map = new char[6];
			ZeroMemory(Map, 6);
			memcpy(Map, &Command[9], 5);
			UI::MapBox->SetText(Map);

			char* String = new char[100];
			sprintf(String, "Loaded map: %s", Map);
			AddChat(String);
			delete[] String;

			delete[] Map;
			Hacks::LoadMap();
			UI::MapBox->SetText(Previous);
		}
		else if(Command[0] != '.')
		{
			return false;
		}
	}
	catch(exception Exception)
	{
		AddChat(Exception.GetException());
	}
	catch(...)
	{
		AddChat("Exception occured.");
	}

	return true;
}

unsigned int Address = 0;
__declspec(naked) void CommandHook ()
{
	__asm
	{
		pushad
		mov Command, eax
	}

	if(HandleCommand() == true)
	{
		__asm
		{
			popad
			add esp, 0xC
			pop edi
			pop esi
			pop ebx
			mov esp, ebp
			pop ebp
			retn
		}
	}

	__asm
	{
		popad
		mov eax, Command
		mov ebx, eax
		push 2
		mov edi, 1
		jmp Address
	}
}

void Misc::SetCommandHook ()
{
	byte JumpHook[] = {0xE9, 0x0, 0x0, 0x0, 0x0};
	*reinterpret_cast<unsigned int*>(&JumpHook[1]) = reinterpret_cast<unsigned int>(CommandHook) - (WoWBase + Script_SendChatMessage + 0x64 + 0x5);
	Write(WoWBase + Script_SendChatMessage + 0x64, JumpHook, 5);
	Address = WoWBase + Script_SendChatMessage + 0x6D;
	return;
}