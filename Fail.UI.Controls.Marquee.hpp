#pragma once

#include "Fail.UI.hpp"

namespace Fail
{
	namespace UI
	{
		namespace Controls
		{
			class Marquee : public Control
			{
			public:
				// Marquee constructor
				inline Marquee (unsigned int X, unsigned int Y, unsigned Width, unsigned int Height, HWND Parent, HINSTANCE Instance, unsigned int Speed = 30)
				{
					InitCommonControls();
					this->Handle = CreateWindowEx(0, PROGRESS_CLASS, nullptr, WS_CHILD | WS_VISIBLE | PBS_MARQUEE, X, Y, Width, Height, Parent, nullptr, Instance, nullptr);
					SendMessage(this->Handle, PBM_SETMARQUEE, 1, Speed);
					return;
				}
			};
		}
	}
}