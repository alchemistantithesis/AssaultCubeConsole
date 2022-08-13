// AssaultCubeConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Process.h"

int main()
{
	DWORD proccessId = Process::GetProcessID(L"ac_client.exe");
	// printf("%lu\n", proccessId);
	uintptr_t baseAddress = Process::GetBaseAddress(proccessId, L"ac_client.exe");
	printf("%lu\n", baseAddress);
}