#pragma once
#include "peb.h"

namespace Peb
{
	PPEB GetProcessPEB()
	{
		// Note : If you are compiling your program as x86, please change the offset (0x60)
		// To the x86 version (0x30).
		return (PPEB)__readgsqword(0x60);
	}

	BOOL CheckForMappedModules(PPEB pProcessPEB)
	{
		PLIST_ENTRY list = &(GetProcessPEB()->Ldr->InLoadOrderModuleList);

		for (PLIST_ENTRY entry = list->Flink; entry != list; ) 
		{
			PLDR_DATA_TABLE_ENTRY module = CONTAINING_RECORD(entry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);

			// takes our current module and verify's it has not been tampered.
			if (Translation::ManualMapped(module))
			{
				return TRUE;
			}
			else
			{
				// Output's the module name. Mainly for debugging purposes.
				printf("Module %ws has not been mapped.\n", module->BaseDllName.Buffer);
			}

			entry = module->InLoadOrderLinks.Flink; // next module in the list.
		}

		return FALSE;
	}
}
