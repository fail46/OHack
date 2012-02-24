#include "OHack.hpp"

handle UI::MainThread;

HMODULE UI::Module;
Window* UI::MainWindow;

View* UI::LoadingView;
View* UI::MainView;

Marquee* UI::ProgressBar;

CheckBox* UI::NoWater;
CheckBox* UI::WaterWalk;
CheckBox* UI::ClimbHack;
CheckBox* UI::NoCollision;
CheckBox* UI::HoverHack;
CheckBox* UI::FlyHack;

EditBox* UI::MorphBox;
EditBox* UI::ScaleBox;
Button* UI::MorphButton;

EditBox* UI::MapBox;
Button* UI::MapButton;

void UI::Create ()
{
	try
	{
		CreateWindowClass(0, UI::UICallback, "OHack", Module);
		MainWindow = new Window ("OHack", "OHack", WS_EX_CLIENTEDGE | WS_EX_DLGMODALFRAME, WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 300, 100, Module);
		MainWindow->EnterMessageLoop();
	}
	catch(exception Exception)
	{
		Notification(MainWindow->GetHandle(), Exception.GetException(), "Exception");
	}

	exit(0);
	return;
}

long __stdcall UI::UICallback (HWND WindowHandle, unsigned int Message, WPARAM wParam, LPARAM lParam)
{
	try
	{
		static Window* ThisWindow = new Window (WindowHandle);
	
		switch(Message)
		{
		case WM_CREATE:
		{
			ProgressBar = new Marquee (5, 5, 282, 25, ThisWindow->GetHandle(), Module);
		
			NoWater = new CheckBox ("No Water", 10, 5, 80, 20, ThisWindow->GetHandle(), 1, Hacks::GetNoWater(), Module);
			WaterWalk = new CheckBox ("Water Walk", 105, 5, 80, 20, ThisWindow->GetHandle(), 2, Hacks::GetWaterWalk(), Module);
			ClimbHack = new CheckBox ("Climb Hack", 10, 30, 80, 20, ThisWindow->GetHandle(), 3, Hacks::GetClimbHack(), Module);
			NoCollision = new CheckBox ("No Collision", 105, 30, 80, 20, ThisWindow->GetHandle(), 6, Hacks::GetNoCollision(), Module);
			HoverHack = new CheckBox ("Hover Hack", 10, 55, 80, 20, ThisWindow->GetHandle(), 7, Hacks::GetHover(), Module);
			FlyHack = new CheckBox ("Fly Hack", 105, 55, 80, 20, ThisWindow->GetHandle(), 8, Hacks::GetFly(), Module);
			
			Text* MorphLabel = new Text ("Model ID:", 0, 100, 55, 15, ThisWindow->GetHandle(), Module);
			Text* ScaleLabel = new Text ("Scale:", 0, 120, 55, 15, ThisWindow->GetHandle(), Module);
			Text* MapLabel = new Text ("Map ID:", 0, 150, 55, 15, ThisWindow->GetHandle(), Module);

			MorphBox = new EditBox (nullptr, ES_NUMBER | ES_CENTER, 55, 100, 80, 15, ThisWindow->GetHandle(), 0, Module);
			ScaleBox = new EditBox (nullptr, ES_CENTER, 55, 120, 80, 15, ThisWindow->GetHandle(), 0, Module);
			MorphBox->LimitCharacters(5);
			ScaleBox->LimitCharacters(5);
			MorphButton = new Button ("Morph", 140, 98, 50, 40, ThisWindow->GetHandle(), 4, Module);

			MapBox = new EditBox (nullptr, ES_NUMBER | ES_CENTER, 55, 150, 80, 15, ThisWindow->GetHandle(), 0, Module);
			MapButton = new Button ("Load", 140, 147, 50, 24, ThisWindow->GetHandle(), 5, Module);

			LoadingView = new View (ThisWindow->GetHandle(), 300, 65, "OHack");
			MainView = new View (ThisWindow->GetHandle(), 200, 205, "OHack");

			LoadingView->AddControl(ProgressBar->GetHandle());

			MainView->AddControl(NoWater->GetHandle());
			MainView->AddControl(WaterWalk->GetHandle());
			MainView->AddControl(ClimbHack->GetHandle());
			MainView->AddControl(MorphBox->GetHandle());
			MainView->AddControl(ScaleBox->GetHandle());
			MainView->AddControl(MorphButton->GetHandle());
			MainView->AddControl(MorphLabel->GetHandle());
			MainView->AddControl(ScaleLabel->GetHandle());
			MainView->AddControl(MapLabel->GetHandle());
			MainView->AddControl(MapBox->GetHandle());
			MainView->AddControl(MapButton->GetHandle());
			MainView->AddControl(NoCollision->GetHandle());
			MainView->AddControl(HoverHack->GetHandle());
			MainView->AddControl(FlyHack->GetHandle());

			LoadingView->Activate();
			return 0;
		}
		case WM_COMMAND:
			CommandHandler(LOWORD(wParam), wParam);
			return 0;

		case WM_CLOSE:
		case WM_DESTROY:
			Notification(ThisWindow->GetHandle(), "You must restart World of Warcraft to unload OHack.");
			return 0;

		default:
			return DefWindowProc(WindowHandle, Message, wParam, lParam);
		}
	}
	catch(exception Exception)
	{
		Notification(MainWindow->GetHandle(), Exception.GetException(), "Exception");
	}

	return 0;
}

void UI::CommandHandler (unsigned int Command, WPARAM wParam)
{
	switch(Command)
	{
	case 1:
		Hacks::SetNoWater(!NoWater->IsChecked());
		break;

	case 2:
		Hacks::SetWaterWalk(!WaterWalk->IsChecked());
		break;

	case 3:
		Hacks::SetClimbHack(!ClimbHack->IsChecked());
		break;

	case 4:
		Hacks::Morph();
		break;

	case 5:
		Hacks::LoadMap();
		break;

	case 6:
		Hacks::SetNoCollision(!NoCollision->IsChecked());
		break;

	case 7:
		Hacks::SetHoverOnFrame = HoverHack->IsChecked() ? 0 : 1;
		break;

	case 8:
		Hacks::SetFlyOnFrame = FlyHack->IsChecked() ? 0 : 1;
		break;
	}

	return;
}