#pragma once
#include "stdafx.h"

namespace Peb
{
	PPEB GetProcessPEB();
	BOOL CheckForMappedModules(PPEB pProcessPEB);
}