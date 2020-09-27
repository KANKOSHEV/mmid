#pragma once
#include "stdafx.h"

namespace Translation
{
	PIMAGE_NT_HEADERS GetNtHeaders(PVOID module);
	BOOL ManualMapped(PLDR_DATA_TABLE_ENTRY module);
}