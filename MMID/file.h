#pragma once
#include "stdafx.h"

namespace File
{
	BOOL ValidImage(PVOID image);
	std::uint8_t* ReadFile(wchar_t* path);
}