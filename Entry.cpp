#include "Hack.hpp"

unsigned int WoWBase = 0;

int __stdcall DllMain (HMODULE Module, unsigned long Reason, void*)
{
	if(Reason != DLL_PROCESS_ATTACH)
	{
		return 0;
	}

	WoWBase = GetMainModule();

	if(Read<byte>(WoWBase + CGGameUI__CanPerformAction) != 0x55)
	{
		Notification(nullptr, "This hack only supports WoW 4.3.2 (15211) x86.", "Unsupported");
		return 0;
	}

	UI::Module = Module;
	UI::MainThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(UI::Create), nullptr, 0, nullptr);
	Misc::KillSwitchThread = CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Misc::LoopKillswitch), nullptr, 0, nullptr);
	if(UI::MainThread == nullptr || Misc::KillSwitchThread == nullptr)
	{
		Notification(nullptr, "Unable to create threads.", "Error");
		return 0;
	}

	return 1;
}