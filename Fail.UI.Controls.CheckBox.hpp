#pragma once

#include "Fail.UI.hpp"

namespace Fail
{
	namespace UI
	{
		namespace Controls
		{
			// Check box control
			class CheckBox : public Control
			{
			public:
				// CheckBox constructor
				inline CheckBox (const char* Text, unsigned int X, unsigned int Y, unsigned Width, unsigned int Height, HWND Parent, unsigned int Command, bool Checked, HINSTANCE Instance)
				{
					this->Handle = CreateWindowEx(0, "button", Text, WS_VISIBLE | WS_CHILD | BS_CHECKBOX, X, Y, Width, Height, Parent,reinterpret_cast<HMENU>(Command), Instance, nullptr);
					SendMessage(this->Handle, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
					return;
				}

				// Return true if the check box is checked, otherwise false
				inline bool IsChecked () const
				{
					return SendMessage(this->Handle, BM_GETCHECK, 0, 0) == BST_CHECKED;
				}

				// Set whether the check box is checked
				inline void SetChecked (bool State) const
				{
					SendMessage(this->Handle, BM_SETCHECK, State == true ? BST_CHECKED : BST_UNCHECKED, 0);
					return;
				}
			};
		}
	}
}