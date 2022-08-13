#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include <TlHelp32.h>

class Process
{
public:
	static DWORD GetProcessID(std::wstring processName);
	static uint32_t GetBaseAddress(DWORD processId, std::wstring moduleName);
	static uintptr_t CalculatePointerAddress(HANDLE handle, uint32_t ptr, std::vector<uint32_t> offsets);
};

