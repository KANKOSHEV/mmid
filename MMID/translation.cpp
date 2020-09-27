#pragma once
#include "translation.h"

namespace Translation
{

	PIMAGE_NT_HEADERS GetNtHeaders(PVOID module)
	{
		auto dosHeader = (PIMAGE_DOS_HEADER)(module);

		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		{
			return {};
		}

		auto ntHeader = (PIMAGE_NT_HEADERS)((UINT64)module + dosHeader->e_lfanew);

		if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
		{
			return {};
		}

		return ntHeader;
	}

	BOOL ManualMapped(PLDR_DATA_TABLE_ENTRY module)
	{
		if (!module)
			return FALSE;

		auto buffer = File::ReadFile(module->FullDllName.Buffer); // full path of image.

		if (!buffer)
			return FALSE;

		printf("Current Module : %ws\n", module->BaseDllName.Buffer); // module name
		printf("SizeOfImage : 0x%x\n", module->SizeOfImage); // size of module image.

		auto runtimeSize = module->SizeOfImage; // size of runtime module image.
		auto diskSize = GetNtHeaders(buffer)->OptionalHeader.SizeOfImage; // size of disk module image.

		if (runtimeSize != diskSize)
		{
			printf("Module %ws has been mapped! Old SizeOfImage was 0x%x\n", module->BaseDllName.Buffer, diskSize);
			return TRUE;
		}

		return FALSE;
	}
}