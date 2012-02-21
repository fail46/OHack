#include "Hack.hpp"

handle Misc::KillSwitchThread;
bool HasChecked = false;

void Misc::LoopKillswitch ()
{
	CheckKillswitch();
	Hacks::Init();
	UI::MainView->Activate();
	delete UI::ProgressBar;
	delete UI::LoadingView;
	HasChecked = true;

	while(true)
	{
		Sleep(30000);
		CheckKillswitch();
	}

	return;
}

void Misc::CheckKillswitch ()
{
	try
	{
		char* Path = new char[261];
		ZeroMemory(Path, 261);

		if(URLDownloadToCacheFile(nullptr, "http://dl.dropbox.com/u/15777331/OHack/KillSwitch.txt", Path, 260, 0, nullptr) != S_OK && HasChecked == false)
		{
			throw exception("Unable to check killswitch: File download failed.");
		}

		std::fstream* KillSwitch = new std::fstream(Path, std::ios::in);
		if(KillSwitch->is_open() == false && HasChecked == false)
		{
			throw exception("Unable to check killswitch: Failed to open file.");
		}

		std::string* Contents = new std::string;
		std::getline(*KillSwitch, *Contents);
		KillSwitch->close();
		delete KillSwitch;
		DeleteFile(Path);
		delete[] Path;

		if(Contents->find("Enabled") == Contents->npos)
		{
			Notification(UI::MainWindow->GetHandle(), Contents->c_str(), "Message");
			exit(0);
		}

		delete Contents;
	}
	catch(exception Exception)
	{
		Notification(UI::MainWindow->GetHandle(), Exception.GetException(), "Exception");
		exit(0);
	}

	return;
}