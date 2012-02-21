#pragma once

#include "Fail.UI.hpp"

namespace Fail
{
	namespace UI
	{
		namespace Controls
		{
			class EditBox : public Control
			{
			public:
				// EditBox constructor
				inline EditBox (const char* Text, unsigned int Style, unsigned int X, unsigned int Y, unsigned Width, unsigned int Height, HWND Parent, unsigned int Command, HINSTANCE Instance)
				{
					this->Handle = CreateWindowEx(0, "edit", Text, WS_CHILD | WS_VISIBLE | Style, X, Y, Width, Height, Parent, reinterpret_cast<HMENU>(Command), Instance, nullptr);
					SendMessage(this->Handle, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
					return;
				}

				// Limit the number of characters in the edit box
				inline void LimitCharacters (unsigned int Characters)
				{
					SendMessage(this->Handle, EM_SETLIMITTEXT, Characters, 0);
					return;
				}
			};
		}
	}
}