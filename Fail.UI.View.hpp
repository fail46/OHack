#pragma once

#pragma warning (push)
#pragma warning (disable : 4996)

#include "Fail.Containers.List.hpp"
#include "Fail.UI.hpp"

namespace Fail
{
	namespace UI
	{
		// View class
		class View : public object
		{
		private:
			// Window enumeration callback
			static unsigned int __stdcall WindowEnumCallback (HWND Window, LPARAM)
			{
				ShowWindow(Window, SW_HIDE);
				return 1;
			}

		protected:
			// Parent window
			HWND Window;

			// Window Size
			unsigned int Width;
			unsigned int Height;

			// Controls list
			Containers::List<HWND> Controls;

			char* Title;

		public:
			// View constructor
			inline View (HWND Parent, unsigned int Width, unsigned int Height, const char* Title)
			{
				this->Window = Parent;
				this->Width = Width;
				this->Height = Height;
				this->Title = new char[strlen(Title) + 2];
				strcpy(this->Title, Title);
				this->Title[strlen(Title) + 1] = 0;
				return;
			}

			// View destructor
			inline ~View ()
			{
				delete[] this->Title;
				return;
			}

			// Add a control to the view
			inline void AddControl (HWND Control)
			{
				this->Controls.AddBack(Control);
				return;
			}

			// Activate the view
			inline void Activate ()
			{
				EnumChildWindows(this->Window, reinterpret_cast<WNDENUMPROC>(WindowEnumCallback), 0);

				unsigned int i = 0;
				while(i < this->Controls.Size())
				{
					ShowWindow(this->Controls[i], SW_SHOW);
					i++;
				}

				SetWindowPos(this->Window, nullptr, 0, 0, this->Width, this->Height, SWP_NOMOVE | SWP_NOZORDER);
				SetWindowText(this->Window, Title);
				return;
			}
		};
	}
}

#pragma warning (pop)