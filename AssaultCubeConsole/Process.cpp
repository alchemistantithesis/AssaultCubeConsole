#include "Process.h"

DWORD Process::GetProcessID(std::wstring processName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnapshot != INVALID_HANDLE_VALUE) 
	{
		PROCESSENTRY32 processEntry { sizeof(PROCESSENTRY32) };
		// processEntry.dwSize = sizeof(PROCESSENTRY32);
		
		if (Process32First(hSnapshot, &processEntry))
		{
			do {
				// printf("%ls\n", processEntry.szExeFile);
				if (!_wcsicmp(processName.c_str(), processEntry.szExeFile))
				{
					CloseHandle(hSnapshot);
					return processEntry.th32ProcessID;
				}
			} while (Process32Next(hSnapshot, &processEntry));
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

uint32_t Process::GetBaseAddress(DWORD processId, std::wstring moduleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE32 | TH32CS_SNAPMODULE, processId);
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 moduleEntry { sizeof(MODULEENTRY32) };
		// moduleEntry.dwSize = sizeof(MODULEENTRY32);

		if (Module32First(hSnapshot, &moduleEntry))
		{
			do {
				printf("%ls\n", moduleEntry.szModule);
				if (!_wcsicmp(moduleName.c_str(), moduleEntry.szModule))
				{
					CloseHandle(hSnapshot);
					return reinterpret_cast<uintptr_t>(moduleEntry.modBaseAddr);
				}
			} while (Module32Next(hSnapshot, &moduleEntry));
		}
	}

	CloseHandle(hSnapshot);
	return 0;
}

uintptr_t Process::CalculatePointerAddress(HANDLE handle, uint32_t ptr, std::vector<uint32_t> offsets)
{
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(handle, (BYTE *)ptr, &ptr, sizeof(ptr), NULL);
		ptr += offsets.at(i);
	}

	return reinterpret_cast<uintptr_t>(ptr);
}
