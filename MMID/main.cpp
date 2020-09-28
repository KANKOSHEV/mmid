#pragma once
#include "stdafx.h"

void checkForInjection()
{
	// check's if any of the module's SizeOfImage has been modified.
	// note : while this is a factor of manual mapping, this does not by any means
	// definitvely mean that the process has been manually mapped.
	auto result = Peb::CheckForMappedModules(Peb::GetProcessPEB());

	if (!result)
	{
		Sleep(750); // keeps everything organized on your screen.
		system("cls"); // clears the console ouput to ease the eye.
		checkForInjection(); // recursive, calls our function again.
	}

	printf("Exitting program..."); // we detected a potential manual mapping threat, so we exit our program.
	Sleep(3500); // keeps everything organized on your screen.
	exit(-1);
}

int main(int argc, char* argv[])
{
	SetConsoleTitle(L"manual mapped injection detector | v1.0");

	auto peb = Peb::GetProcessPEB(); // gets our process peb.

	printf("Process PEB : 0x%x\n", peb); // outputs the pointer to our process PEB (for debugging purposes).

	std::thread anti_injection(checkForInjection); // creates a new thread to continously scan modules.

	std::getchar();
	
	anti_injection.detach();

	return 0;
}
