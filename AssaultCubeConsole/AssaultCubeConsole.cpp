// AssaultCubeConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Process.h"

int main()
{
	DWORD processId = Process::GetProcessID(L"ac_client.exe");
	uintptr_t baseAddress = Process::GetBaseAddress(processId, L"ac_client.exe");
	
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
	if (hProcess) 
	{
		printf("Module Base Address:\n\t0x%X\n", baseAddress);

		// Base Address
		uintptr_t entityBaseAddress = baseAddress + 0x10F4F4;
		printf("Entity Address:\n\t0x%X\n", entityBaseAddress);

		// Current Weapon Ammo
		std::vector<uintptr_t> currentWeaponAmmoOffsets{0x374, 0x14, 0x0};
		uintptr_t currentWeaponAmmoAddress = Process::CalculatePointerAddress(hProcess, entityBaseAddress, currentWeaponAmmoOffsets);
		printf("Current Weapon Ammo Address:\n\t0x%X\n", currentWeaponAmmoAddress);

		uint32_t currentWeaponAmmo = 0;
		ReadProcessMemory(hProcess, reinterpret_cast<BYTE*>(currentWeaponAmmoAddress), &currentWeaponAmmo, sizeof(currentWeaponAmmo), NULL);
		printf("Current Weapon Ammo:\n\t%lu\n", currentWeaponAmmo);

		uint32_t infiniteAmmo = 1337;
		WriteProcessMemory(hProcess, reinterpret_cast<BYTE*>(currentWeaponAmmoAddress), &infiniteAmmo, sizeof(infiniteAmmo), NULL);

		currentWeaponAmmo = 0;
		ReadProcessMemory(hProcess, reinterpret_cast<BYTE*>(currentWeaponAmmoAddress), &currentWeaponAmmo, sizeof(currentWeaponAmmo), NULL);
		printf("New Weapon Ammo:\n\t%lu\n", currentWeaponAmmo);

		CloseHandle(hProcess);
	}

	return 0;
}