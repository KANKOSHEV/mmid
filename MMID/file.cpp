#pragma once
#include "file.h"

namespace File
{
	BOOL ValidImage(PVOID image)
	{
		auto dosHeader = (PIMAGE_DOS_HEADER)(image);

		if (dosHeader->e_magic != IMAGE_DOS_SIGNATURE)
		{
			return FALSE;
		}

		auto ntHeader = (PIMAGE_NT_HEADERS)((UINT64)image + dosHeader->e_lfanew);
		
		if (ntHeader->Signature != IMAGE_NT_SIGNATURE)
		{
			return FALSE;
		}

		return TRUE;
	}

	std::uint8_t* ReadFile(wchar_t* path)
	{
		HANDLE MappedObject;
		HANDLE File;
		PBYTE Image = 0;

		File = CreateFile(path, GENERIC_READ, FILE_SHARE_READ, NULL, 
			OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (File == INVALID_HANDLE_VALUE)
		{
			printf("Failed to find input path.\n");
			return {};
		}

		MappedObject = CreateFileMappingA(File, NULL,
			PAGE_READONLY, 0, 0, NULL);
		
		if (MappedObject == INVALID_HANDLE_VALUE)
		{
			printf("Failed to map view of file.\n");
			return {};
		}

		Image = (PBYTE)MapViewOfFile(MappedObject, FILE_MAP_READ, 0, 0, 0);

		CloseHandle(MappedObject);
		CloseHandle(File);

		if (ValidImage(Image))
		{
			return Image;
		}

		return {};
	}
}