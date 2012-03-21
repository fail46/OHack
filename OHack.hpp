#pragma once

#define ThisVersion 10

#include <Windows.h>
#include <UrlMon.h>
#include <Psapi.h>

#include <fstream>
#include <string>

#include <detours.h>

#include "Fail.Dialog.hpp"
#include "Fail.Exception.hpp"
#include "Fail.Handle.hpp"
#include "Fail.Loops.hpp"
#include "Fail.Memory.Local.hpp"
#include "Fail.Object.hpp"
#include "Fail.UI.hpp"
#include "Fail.UI.View.hpp"
#include "Fail.UI.Controls.Button.hpp"
#include "Fail.UI.Controls.CheckBox.hpp"
#include "Fail.UI.Controls.EditBox.hpp"
#include "Fail.UI.Controls.Marquee.hpp"
#include "Fail.UI.Controls.Text.hpp"

#include "Offsets.hpp"

#pragma comment (lib, "UrlMon.lib")
#pragma comment (lib, "Psapi.lib")

using namespace Fail::Dialog;
using namespace Fail::Memory::Local;
using namespace Fail::UI;
using namespace Fail::UI::Controls;
using Fail::exception;
using Fail::handle;

typedef unsigned char byte;

extern unsigned int WoWBase;

namespace UI
{
	extern handle MainThread;

	extern HMODULE Module;

	extern Window* MainWindow;

	extern View* LoadingView;
	extern View* MainView;

	extern Marquee* ProgressBar;

	extern CheckBox* NoWater;
	extern CheckBox* WaterWalk;
	extern CheckBox* ClimbHack;
	extern CheckBox* NoCollision;
	extern CheckBox* HoverHack;
	extern CheckBox* FlyHack;

	extern EditBox* MorphBox;
	extern EditBox* ScaleBox;
	extern Button* MorphButton;

	extern EditBox* MapBox;
	extern Button* MapButton;

	void Create ();
	long __stdcall UICallback (HWND Window, unsigned int Message, WPARAM wParam, LPARAM lParam);
	void CommandHandler (unsigned int Command, WPARAM wParam);
}

namespace Hacks
{
	extern int SetFlyOnFrame;
	extern int SetHoverOnFrame;
	extern int MapID;

	void Init ();

	void StopFall ();
	void Tracking (const char* Track);

	void Morph ();
	void LoadMap ();

	void SetNoWater (bool State);
	bool GetNoWater ();

	void SetWaterWalk (bool State);
	bool GetWaterWalk ();

	void SetClimbHack (bool State);
	bool GetClimbHack ();

	void SetNoCollision (bool State);
	bool GetNoCollision ();

	void SetHover (bool State);
	bool GetHover ();

	void SetFly (bool State);
	bool GetFly ();
}

namespace Misc
{
	extern handle KillSwitchThread;

	void LoopKillswitch ();
	void CheckKillswitch ();
	void SetCommandHook ();
}

namespace WoW
{
	extern bool (__thiscall* Render)(unsigned int);
	bool __fastcall FrameHook (unsigned int This);

	bool IsInGame ();
	void AddChatMessage (const char* Message);
	unsigned int GetPlayer ();
	unsigned int GetTarget ();
	void DoString (const char* String);
}

namespace Warden
{
	extern bool HasEnabled;

	void Enable ();
}