#include "OHack.hpp"

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

		std::string* Contents = new std::string[2];
		std::getline(*KillSwitch, Contents[0]);
		std::getline(*KillSwitch, Contents[1]);
		KillSwitch->close();
		delete KillSwitch;
		DeleteFile(Path);
		delete[] Path;

		if(Contents->find("Enabled") == Contents->npos)
		{
			if(HasChecked == false)
			{
				Notification(UI::MainWindow->GetHandle(), Contents->c_str(), "Message");
			}

			exit(0);
		}

		static unsigned int Version = ThisVersion;
		unsigned int NewVersion = atoi(Contents[1].c_str());
		if(NewVersion > Version)
		{ 
			if(Question(UI::MainWindow->GetHandle(), "A new version of OHack is available. Open the download page?" , "New Version") == true)
			{
				ShellExecute(nullptr, "open", "http://dl.dropbox.com/u/15777331/OHack/Redirect.html", nullptr, nullptr, 0);
			}

			Version = NewVersion;
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