#pragma once

#pragma warning (push)
#pragma warning (disable : 4482)

#include <Windows.h>
#include <TlHelp32.h>

#include "Fail.Exception.hpp"
#include "Fail.Loops.hpp"
#include "Fail.Types.hpp"

namespace Fail
{
	namespace Memory
	{
		// Memory Protection
		enum Protection : unsigned int
		{
			NoAccess = 0x1,
			Read = 0x2,
			ReadWrite = 0x4,
			WriteCopy = 0x8,
			Execute = 0x10,
			ExecuteRead = 0x20,
			ExecuteReadWrite = 0x40,
			ExecuteWriteCopy = 0x80
		};

		// Functions for local process memory editing
		namespace Local
		{
			// Get an object and return by reference
			template <typename Type>
			inline Type& get (uint Address)
			{
				return *reinterpret_cast<Type*>(Address.AsPointer());
			}

			// Get a pointer to the main module
			inline uint GetMainModule ()
			{
				return GetModuleHandle(nullptr);
			}

			// Get a pointer to a module
			inline uint GetModule (const char* Module)
			{
				return GetModuleHandle(Module);
			}

			// Get a handle to the main thread
			inline void* GetMainThread ()
			{
				THREADENTRY32 Thread;
				ZeroMemory(&Thread, sizeof(Thread));
				Thread.dwSize = sizeof(Thread);
				void* Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, GetCurrentProcessId());
				Thread32Next(Snapshot, &Thread);
				if(Thread.th32OwnerProcessID != GetCurrentProcessId())
				{
					throw exception("Unable to get main thread.");
				}

				CloseHandle(Snapshot);
				return OpenThread(THREAD_ALL_ACCESS, false, Thread.th32ThreadID);
			}

			// Protect memory and return the old protection
			inline Protection Protect (uint Address, uint Size, Protection NewProtection)
			{
				unsigned long OldProtection = 0;
				if(VirtualProtect(Address.AsPointer(), Size, NewProtection, &OldProtection) == 0)
				{
					throw exception("Unable to change memory protection: VirtualProtect failed.");
				}

				return Protection(OldProtection);
			}

			// Read a copy of an object from memory
			template <typename Type>
			Type& ReadCopy (uint Address)
			{
				Type Object;
				Protection OldProtection = Protect(Address, sizeof(Object), Protection::WriteCopy);
				memcpy(&Object, Address.AsPointer(), sizeof(Object));
				Protect(Address, sizeof(Object), OldProtection);
				return Object;
			}

			// Read an object from memory. The memory must be readable already.
			template <typename Type>
			inline Type& Read (uint Address)
			{
				return *reinterpret_cast<Type*>(Address.AsPointer());
			}

			// Write an object into memory
			template <typename Type>
			void Write (uint Address, const Type& Object)
			{
				Protection OldProtection = Protect(Address, sizeof(Object), Protection::ReadWrite);

				memcpy(Address.AsPointer(), &Object, sizeof(Object));
				if(*reinterpret_cast<const unsigned char*>(Address.AsPointer()) != *reinterpret_cast<const unsigned char*>(&Object))
				{
					throw exception("Memory write failed.");
				}

				Protect(Address, sizeof(Object), OldProtection);
				FlushInstructionCache(GetCurrentProcess(), Address.AsPointer(), sizeof(Object));
				return;
			}

			// Write an array of bytes into memory
			inline void Write (uint Address, const unsigned char* Bytes, uint Size)
			{
				Protection OldProtection = Protect(Address, Size, Protection::ReadWrite);

				memcpy(Address.AsPointer(), Bytes, Size);
				if(*reinterpret_cast<unsigned char*>(Address.AsPointer()) != Bytes[0])
				{
					throw exception("Memory write failed.");
				}

				Protect(Address, Size, OldProtection);
				FlushInstructionCache(GetCurrentProcess(), Address.AsPointer(), Size);
				return;
			}
		}
	}
}

#pragma warning (pop)