// AssaultCubeConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Process.h"

int main()
{
	printf("%lu\n", Process::GetProcessID(L"ac_client.exe"));
}