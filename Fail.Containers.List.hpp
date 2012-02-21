#pragma once

#include <deque>

#include "Fail.Object.hpp"

namespace Fail
{
	// Container classes
	namespace Containers
	{
		template <typename T>
		class List : public object
		{
		public:
			// Default constructor
			inline List ()
			{
				return;
			}

			// Add an object to the back of the list
			inline void Add (T Object)
			{
				this->Deque.push_back(Object);
				return;
			}

			// Add an object to the front of the list
			inline void AddBack (T Object)
			{
				this->Deque.push_front(Object);
				return;
			}

			// Remove the object at the front of the list
			inline void RemoveFront ()
			{
				this->Deque.pop_front();
				return;
			}

			// Remove the object at the back of the list
			inline void RemoveBack ()
			{
				this->Deque.pop_back();
				return;
			}

			// Get and remove the object at the front of the list
			T GetAndRemoveFront ()
			{
				T Object;
				memcpy(&Object, &this->Deque.front(), sizeof(T));
				this->RemoveFront();
				return Object;
			}

			// Get and remove the object at the back of the list
			T GetAndRemoveBack ()
			{
				T Object;
				memcpy(&Object, &this->Deque.back(), sizeof(T));
				this->RemoveBack();
				return Object;
			}

			// Find an object in the list and return its position. -1 if not found.
			int Find (T& Object)
			{
				unsigned int i = 0;
				while(i < this->Deque.size())
				{
					if(this->Deque[i] == Object)
					{
						return i;
					}
					i++;
				}

				return -1;
			}

			// Clear the list
			inline void Clear ()
			{
				this->Deque.clear();
				return;
			}

			// Check if the list is empty
			inline bool Empty () const
			{
				return this->Deque.empty;
			}

			// Insert an object into the list
			inline void Insert (T Object, unsigned int Position)
			{
				this->Deque.insert(Position, Object);
				return;
			}

			// Swap 2 objects in the list
			inline void Swap (unsigned int FirstObject, unsigned int SecondObject)
			{
				T* Object = new T;
				*Object = this->Deque[FirstObject];
				this->Deque[FirstObject] = this->Deque[SecondObject];
				this->Deque[SecondObject] = *Object;
				delete Object;
				return;
			}

			// Get the number of objects in the list
			inline unsigned int Size () const
			{
				return this->Deque.size();
			}

			// Get the list member at i
			T& At (unsigned int i)
			{
				if(i >= this->Deque.size() || i < 0)
				{
					throw std::exception("Unable to get List member: Out of range.");
				}

				return this->Deque[i];
			}

			// Array access operator
			inline T& operator [] (unsigned int i)
			{
				return this->At(i);
			}

			// Copy operator
			List<T>& operator = (const List<T>& Other)
			{
				unsigned int i = 0;
				while(i < Other.Size())
				{
					this->At[i] = const_cast<List<T>>(Other)[i];
					i++;
				}

				return *this;
			}

			// Equality operator
			bool operator == (const List<T>& Other)
			{
				if(this->ObjectSize != Other.ObjectSize)
				{
					return false;
				}

				unsigned int i = 0;
				while(i < Other.Size())
				{
					if(this->At(i) != const_cast<List<T>>(Other)[i])
					{
						return false;
					}
					i++;
				}
				return true;
			}

			// Inequality operator
			inline bool operator != (const List<T>& Other)
			{
				return !this->operator ==(Other);
			}

			// Add an object to the back of the list
			inline void operator += (T Object)
			{
				this->AddBack(Object);
				return;
			}

		protected:
			// Deque object
			std::deque<T> Deque;
		};
	}
}