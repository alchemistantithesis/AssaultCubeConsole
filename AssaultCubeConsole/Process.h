#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

class Process
{
public:
	static DWORD GetProcessID(std::wstring processName);
	static uintptr_t GetBaseAddress(DWORD processId, std::wstring module);
	static uintptr_t CalculatePointerAddress(HANDLE handle, uintptr_t ptr, std::vector<uint32_t> offsets);
};

