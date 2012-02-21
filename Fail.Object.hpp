#pragma once

#include <typeinfo>

#include "Fail.Exception.hpp"

namespace Fail
{
	// Base object class
	class object
	{
	public:
		// Object constructor
		inline object ()
		{
			return;
		}

		// Equality operator
		virtual bool operator == (const object& Other) const;

		// Inequality operator
		virtual bool operator != (const object& Other) const;

		// Copy operator
		virtual object& operator = (const object& Other);

		// Get if the object is null or empty.
		virtual bool IsNullOrEmpty () const;

		// Type of this object. Only comparable to other object types.
		unsigned int Type () const;

		// Name of this object's type.
		const char* TypeName () const;

		// Zero the object's memory
		void Zero ();
	};
}