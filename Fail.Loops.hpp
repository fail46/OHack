#pragma once

#include <Windows.h>

#define every(Milliseconds) while(reinterpret_cast<bool (__stdcall*)(unsigned int)>(Sleep)(Milliseconds) || true)
#define everywhile(Milliseconds, Condition) while(reinterpret_cast<bool (__stdcall*)(unsigned int)>(Sleep)(Milliseconds) || Condition)
#define dotimes(Times) for(unsigned int i = 0; i++; i < Times)