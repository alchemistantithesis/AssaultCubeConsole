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
				printf("%ls\n", processEntry.szExeFile);
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

uintptr_t Process::GetBaseAddress(DWORD processId, std::wstring module)
{
	return uintptr_t();
}

uintptr_t Process::CalculatePointerAddress(HANDLE handle, uintptr_t ptr, std::vector<uint32_t> offsets)
{
	return uintptr_t();
}
