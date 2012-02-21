#pragma once

#pragma warning (push)
#pragma warning(disable : 4996)

#include <cmath>
#include <cstdlib>

namespace Fail
{
	class byte
	{
	public:
		// Default constructor
		inline byte ()
		{
			this->Value = 0;
			return;
		}

		// Byte constructor
		inline byte (unsigned char Byte)
		{
			this->Value = Byte;
			return;
		}

		// Return the byte as a string.
		inline const char* AsString (bool Hex = false) const
		{
			char* String = new char[Hex ? 3 : 4];
			itoa(this->Value, String, Hex ? 16 : 10);
			return String;
		}

		// Unsigned char operator
		inline operator unsigned char ()
		{
			return this->Value;
		}

		// Const unsigned char operator
		inline operator const unsigned char () const
		{
			return this->Value;
		}
		
	protected:
		// Byte value
		unsigned char Value;
	};

	// Unsigned integer class
	class uint
	{
	public:
		// Default constructor
		inline uint ()
		{
			this->Value = 0;
			return;
		}

		// Unsigned int constructor
		inline uint (unsigned int UInt)
		{
			this->Value = UInt;
			return;
		}

		// Void* constructor
		inline uint (void* Pointer)
		{
			this->Value = reinterpret_cast<unsigned int>(Pointer);
			return;
		}

		// Unsigned int operator
		inline operator unsigned int ()
		{
			return this->Value;
		}

		// Const unsigned int operator
		inline operator const unsigned int () const
		{
			return this->Value;
		}

		// Void* operator
		inline operator void* ()
		{
			return this->AsPointer();
		}

		// Return the object as a pointer
		inline void* AsPointer () const
		{
			return reinterpret_cast<void*>(this->Value);
		}

		// Return the object as a string
		inline const char* AsString (bool Hex = false) const
		{
			char* String = new char[Hex ? 9 : 10];
			itoa(this->Value, String, Hex ? 16 : 10);
			return String;
		}

	protected:
		// Unsigned int value
		unsigned int Value;
	};

	// Signed integer class
	class sint
	{
	public:
		// Default constructor
		inline sint ()
		{
			this->Value = 0;
			return;
		}

		// Int constructor
		inline sint (signed int Int)
		{
			this->Value = Int;
			return;
		}

		// Int operator
		inline operator signed int ()
		{
			return this->Value;
		}

		// Get the value of the sint
		inline signed int Get () const
		{
			return this->Value;
		}

		// Return the object as a string
		inline const char* AsString (bool Hex = false)
		{
			char* String = new char[Hex ? 10 : 11];
			itoa(this->Value, String, Hex ? 16 : 10);
			return String;
		}

	private:
		// Signed int value
		int Value;
	};
}

#pragma warning (pop)