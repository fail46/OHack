#pragma once

#include "Fail.UI.hpp"

namespace Fail
{
	namespace UI
	{
		namespace Controls
		{
			class Text : public Control
			{
			public:
				inline Text (const char* Text, unsigned int X, unsigned int Y, unsigned Width, unsigned int Height, HWND Parent, HINSTANCE Instance)
				{
					this->Handle = CreateWindowEx(0, "static", Text, WS_CHILD | WS_VISIBLE | SS_CENTER, X, Y, Width, Height, Parent, nullptr, Instance, nullptr);
					SendMessage(this->Handle, WM_SETFONT, reinterpret_cast<WPARAM>(GetStockObject(DEFAULT_GUI_FONT)), 0);
					return;
				}
			};
		}
	}
}