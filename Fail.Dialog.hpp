#pragma once

#include <Windows.h>

namespace Fail
{
	// Dialog functions and classes
	namespace Dialog
	{
		// A dialog box with an OK button.
		inline void Notification (HWND Parent, const char* Text, const char* Title = "")
		{
			MessageBox(Parent, Text, Title, MB_OK | MB_ICONINFORMATION);
			return;
		}

		// A dialog box with a Yes and a No button. Returns true if Yes is clicked, or false if No is clicked.
		inline bool Question (HWND Parent, const char* Text, const char* Title = "")
		{
			return MessageBox(Parent, Text, Title, MB_YESNO | MB_ICONQUESTION) == IDYES;
		}

		// A dialog box with an OK and a Cancel button. Returns true if OK is clicked, or false if Cancel is clicked.
		inline bool Confirmation (HWND Parent, const char* Text, const char* Title = "")
		{
			return MessageBox(Parent, Text, Title, MB_OKCANCEL | MB_ICONWARNING) == IDOK;
		}

		// A dialog box with a Retry and a Cancel button. Returns true if Retry is click, or false if Cancel is clicked.
		inline bool Retry (HWND Parent, const char* Text, const char* Title = "")
		{
			return MessageBox(Parent, Text, Title, MB_RETRYCANCEL | MB_ICONQUESTION) == IDRETRY;
		}
	}
}