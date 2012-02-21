#pragma once

#include <Windows.h>

#include "Fail.Object.hpp"

namespace Fail
{
	// Closing handle
	class handle : public Fail::object
	{
	public:
		// Default constructor
		inline handle ()
		{
			this->Handle = nullptr;
			return;
		}

		// Handle constructor
		inline handle (void* Handle)
		{
			this->Handle = Handle;
			return;
		}

		// Handle destructor
		inline ~handle ()
		{
			CloseHandle(this->Handle);
			return;
		}

		// Close the handle
		inline void Close ()
		{
			this->~handle();
			return;
		}

		// Void* operator
		inline operator void* ()
		{
			return this->Handle;
		}

		// Copy operator
		inline handle& operator = (handle Other)
		{
			DuplicateHandle(GetCurrentProcess(), Other, GetCurrentProcess(), &this->Handle, 0, false, DUPLICATE_SAME_ACCESS);
			return *this;
		}

		// Get the handle's value
		inline void* GetHandle () const
		{
			return this->Handle;
		}

	protected:
		// Handle value
		void* Handle;
	};
}