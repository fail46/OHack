#pragma once

#include "Fail.UI.hpp"

namespace Fail
{
	namespace UI
	{
		namespace Controls
		{
			// Button control
			class Button : public Control
			{
			public:
				// Button constructor
				inline Button (const char* Text, unsigned int X, unsigned int Y, unsigned Width, unsigned int Height, HWND Parent, unsigned int Command, HINSTANCE Instance)
				{
					this->Handle = CreateWindowEx(0, "button", Text, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, X, Y, Width, Height, Parent, reinterpret_cast<HMENU>(Command), Instance, nullptr);
					SendMessage(this->Handle, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
					return;
				}

				// Push the button
				inline void Push () const
				{
					SendMessage(this->Handle, BM_CLICK, 0, 0);
					return;
				}
			};
		}
	}
}