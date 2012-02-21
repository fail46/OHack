#include "Fail.UI.hpp"

void Fail::UI::CreateWindowClass (unsigned long Style, WNDPROC MessageHandler, const char* ClassName, HINSTANCE Instance, unsigned int BackgroundColor, HCURSOR Cursor, HICON Icon, HICON SmallIcon)
{
	WNDCLASSEX WindowClass;
	ZeroMemory(&WindowClass, sizeof(WindowClass));

	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.hbrBackground = reinterpret_cast<HBRUSH>(BackgroundColor);
	WindowClass.hCursor = Cursor;
	WindowClass.hIcon = Icon;
	WindowClass.hIconSm = SmallIcon;
	WindowClass.hInstance = Instance;
	WindowClass.lpfnWndProc = MessageHandler;
	WindowClass.lpszClassName = ClassName;
	WindowClass.style = Style;

	if(RegisterClassEx(&WindowClass) == 0)
	{
		throw Fail::exception("Window class registration failed.");
	}
	return;
}

Fail::UI::Window::Window (const char* ClassName, const char* WindowName, unsigned long ExStyle, unsigned long Style, unsigned int X, unsigned int Y, unsigned int Width, unsigned int Height, HINSTANCE Instance, HWND Parent)
{
	this->Handle = CreateWindowEx(ExStyle, ClassName, WindowName, Style, X, Y, Width, Height, Parent, nullptr, Instance, nullptr);
	if(this->Handle == nullptr)
	{
		throw Fail::exception("Window creation failed.");
	}

	this->Update();
	this->Show(true);
	return;
}

void Fail::UI::Window::Focus (bool Focus) const
{
	if(Focus == true)
	{
		SwitchToThisWindow(this->Handle, 0);
	}
	else
	{
		SwitchToThisWindow(0, 0);
	}

	return;
}

const char* Fail::UI::Window::GetTitle () const
{
	unsigned int Length = GetWindowTextLength(this->Handle);
	char* Title = new char[Length];
	GetWindowText(this->Handle, Title, Length);
	return Title;
}

Fail::UI::Window::Location& Fail::UI::Window::GetPosition () const
{
	RECT Rect;
	GetWindowRect(this->Handle, &Rect);
	Window::Location* Location = new Window::Location;
	Location->X = Rect.left;
	Location->Y = Rect.top;
	return *Location;
}

Fail::UI::Window::Size& Fail::UI::Window::GetSize () const
{
	RECT Rect;
	GetWindowRect(this->Handle, &Rect);
	Size* WindowSize = new Size; 
	WindowSize->X = Rect.right - Rect.left;
	WindowSize->Y = Rect.bottom - Rect.top;
	return *WindowSize;
}

const char* Fail::UI::Controls::Control::GetText () const
{
	unsigned int Length = GetWindowTextLength(this->Handle);
	char* Text = new char[Length + 2];
	GetWindowText(this->Handle, Text, Length + 1);
	return Text;
}