#pragma once

#include <Windows.h>
#include <CommCtrl.h>

#include <map>
#include <typeinfo>

#include "Fail.Exception.hpp"
#include "Fail.Object.hpp"

#pragma comment (lib, "ComCtl32.lib")

namespace Fail
{
	// User interface classes and functions
	namespace UI
	{
		// Control classes and functions
		namespace Controls
		{
			// Control parent class. Internal; don't use.
			class Control : public object
			{
			protected:
				// Control handle
				HWND Handle;

			public:
				// Default constructor
				inline Control ()
				{
					return;
				}

				// Control destructor
				inline ~Control ()
				{
					DestroyWindow(this->Handle);
					return;
				}

				// Get a handle to the control
				inline HWND GetHandle () const
				{
					return this->Handle;
				}

				// Change whether the control is visible or not
				inline void SetVisible (bool Visible) const
				{
					ShowWindow(this->Handle, Visible ? SW_SHOW : SW_HIDE);
					return;
				}

				// Set the control's text. Not all controls are supported.
				inline void SetText (const char* Text) const
				{
					SetWindowText(this->Handle, Text);
					return;
				}

				// Get the control's text. Not all controls are supported.
				const char* GetText () const;
			};
		}

		// Window object
		class Window : public object
		{
		public:
			// Window location
			class Location
			{
			public:
				Location ()
				{
					this->X = 0;
					this->Y = 0;
					return;
				}

				unsigned int X;
				unsigned int Y;
			};

			// Window size
			class Size
			{
			public:
				Size ()
				{
					this->X = 0;
					this->Y = 0;
					return;
				}

				unsigned int X;
				unsigned int Y;
			};

			// Create a window and construct the object
			Window (const char* ClassName, const char* WindowName, unsigned long ExStyle, unsigned long Style, unsigned int X, unsigned int Y, unsigned int Width, unsigned int Height, HINSTANCE Instance, HWND Parent = nullptr);

			// Construct the object with an already existing window
			inline Window (HWND Window)
			{
				this->Handle = Window;
				return;
			}

			// Update the window
			inline void Update () const
			{
				UpdateWindow(this->Handle);
				return;
			}

			// Show or hide the window
			inline void Show (bool Show) const
			{
				ShowWindow(this->Handle, Show ? SW_SHOW : SW_HIDE);
				return;
			}

			// Close the window
			inline void Close () const
			{
				CloseWindow(this->Handle);
				return;
			}

			// Destroy the window
			inline void Destroy () const
			{
				DestroyWindow(this->Handle);
				return;
			}

			// Get the window handle
			inline HWND GetHandle () const
			{
				return this->Handle;
			}

			// Focus or unfocus the window
			void Focus (bool Focus = true) const;

			// Get if the window is focused
			inline bool IsFocused () const
			{
				return GetForegroundWindow() == this->Handle;
			}

			// Get if the window is visible
			inline bool IsVisible () const
			{
				return IsWindowVisible(this->Handle) != 0;
			}

			// Set if the window is visible
			inline void SetVisible (bool Show) const
			{
				ShowWindow(this->Handle, Show ? SW_SHOW : SW_HIDE);
				return;
			}

			// Set the window's title
			inline void SetTitle (const char* Title) const
			{
				SetWindowText(this->Handle, Title);
				return;
			}
			
			// Get the window's title
			const char* GetTitle () const;

			// Set the window's position
			inline void SetPosition (unsigned int X, unsigned int Y) const
			{
				SetWindowPos(this->Handle, nullptr, X, Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
				return;
			}

			// Get the window's position
			Location& GetPosition () const;

			// Set the window's size
			inline void SetSize (unsigned int X, unsigned int Y) const
			{
				SetWindowPos(this->Handle, nullptr, 0, 0, X, Y, SWP_NOMOVE | SWP_NOZORDER);
				return;
			}

			// Get the window's size
			Size& GetSize () const;

			// Enter the message loop. Does not return until the window exits. Must be called from the same thread that created the window.
			inline void EnterMessageLoop () const
			{
				MSG Msg;
				while(GetMessage(&Msg, nullptr, 0, 0) > 0)
				{
					TranslateMessage(&Msg);
					DispatchMessage(&Msg);
				}

				return;
			}

			// Assignment operator
			void operator = (const Window& Other)
			{
				this->Handle = Other.Handle;
				return;
			}

			// Equality operator
			bool operator == (const Window& Other) const
			{
				return this->Handle == Other.Handle;
			}

			// Inequality operator
			bool operator != (const Window& Other) const
			{
				return this->Handle != Other.Handle;
			}

		protected:
			// Window handle
			HWND Handle;
		};

		// Create and register a new window class
		void CreateWindowClass (unsigned long Style, WNDPROC MessageHandler, const char* ClassName, HINSTANCE Instance, unsigned int BackgroundColor = COLOR_WINDOW, HCURSOR Cursor = nullptr, HICON Icon = nullptr, HICON SmallIcon = nullptr);
	}
}