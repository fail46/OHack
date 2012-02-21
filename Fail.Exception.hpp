#pragma once

#pragma warning (push)
#pragma warning (disable : 4996)

#include <Windows.h>

#include <cstdio>

namespace Fail
{
	// Exception class
	class exception
	{
	public:
		// Default constructor
		inline exception ()
		{
			register unsigned int Length = strlen("Exception occurred.") + 1;
			this->String = new char[Length];
			ZeroMemory(this->String, Length);
			strcpy(this->String, "Exception occurred.");
			return;
		}

		// Message constructor
		inline exception (const char* Message)
		{
			register unsigned int Length = strlen(Message) + 13;
			this->String = new char[Length];
			ZeroMemory(this->String, Length);
			sprintf(this->String, "Exception: %s.", Message);
			return;
		}

		// Message and function constructor
		inline exception (const char* Message, const char* Function)
		{
			register unsigned int Length = strlen(Message) + strlen(Function) + strlen("Exception occurred in function: %s.\n%s") - 3;
			this->String = new char[Length];
			ZeroMemory(this->String, Length);
			sprintf(this->String, "Exception occurred in function: %s.\n%s", Function, Message);
			return;
		}

		// Exception destructor
		inline ~exception ()
		{
			delete[] this->String;
			return;
		}

		// Get the formatted exception string
		inline const char* GetException () const
		{
			return this->String;
		}

	protected:
		char* String;
	};
}

#pragma warning (pop)