#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

class Process
{
public:
	static DWORD GetProcessID(std::wstring processName);
	static uintptr_t GetBaseAddress(DWORD processId, std::wstring moduleName);
	static uintptr_t CalculatePointerAddress(HANDLE handle, uintptr_t ptr, std::vector<uintptr_t> offsets);
};

