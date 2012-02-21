#include "Fail.Object.hpp"

bool Fail::object::operator == (const object& Other) const
{
	unsigned int i = 0;
	while(i < sizeof(*this))
	{
		if(reinterpret_cast<unsigned char*>(const_cast<object*>(this))[i] != reinterpret_cast<unsigned char*>(const_cast<object*>(&Other))[i])
		{
			return false;
		}
	}

	return true;
}

bool Fail::object::operator != (const object& Other) const
{
	return !this->operator==(Other);
}

Fail::object& Fail::object::operator = (const object& Other)
{
	if(sizeof(*this) != sizeof(Other))
	{
		throw Fail::exception("Attempt to copy an object to an object of an incompatible type.", __FUNCTION__);
	}

	unsigned int i = 0;
	if(sizeof(*this) % 4 != 0)
	{
		// Use bytes so that only the object is copied
		while(i < sizeof(*this))
		{
			reinterpret_cast<unsigned char*>(this)[i] = reinterpret_cast<unsigned char*>(const_cast<object*>(&Other))[i];
			i++;
		}
	}
	else
	{
		// Use 4-byte integers if possible for faster copy speed
		while(i < sizeof(*this) / 4)
		{
			reinterpret_cast<unsigned int*>(this)[i] = reinterpret_cast<unsigned int*>(const_cast<object*>(&Other))[i];
			i++;
		}
	}

	return *this;
}

unsigned int Fail::object::Type() const
{
	return typeid(*this).hash_code();
}

const char* Fail::object::TypeName() const
{
	return typeid(*this).name();
}

void Fail::object::Zero ()
{
	memset(this, 0, sizeof(*this));
	return;
}

bool Fail::object::IsNullOrEmpty () const
{
	unsigned int i = 0;
	while(i < sizeof(*this))
	{
		if(*reinterpret_cast<unsigned char*>(const_cast<object*>(this)) != 0)
		{
			return false;
		}
		i++;
	}

	return true;
}