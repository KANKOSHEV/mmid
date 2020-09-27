#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING;

typedef UNICODE_STRING* PUNICODE_STRING;
typedef const UNICODE_STRING* PCUNICODE_STRING;

typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	union
	{
		LIST_ENTRY InInitializationOrderLinks;
		LIST_ENTRY InProgressLinks;
	};
	PVOID           DllBase;
	PVOID           Entrypoint;
	ULONG           SizeOfImage;
	UNICODE_STRING  FullDllName;
	UNICODE_STRING  BaseDllName;
} LDR_DATA_TABLE_ENTRY, * PLDR_DATA_TABLE_ENTRY;

typedef struct _PEB_LDR_DATA
{
	ULONG       Length;
	UCHAR       Initialized;
	PVOID       SsHandle;
	LIST_ENTRY  InLoadOrderModuleList;
	LIST_ENTRY  InMemoryOrderModuleList;
	LIST_ENTRY  InInitializationOrderModuleList;
} PEB_LDR_DATA, * PPEB_LDR_DATA;

typedef struct _RTL_USER_PROCESS_PARAMETERS {
	BYTE Reserved1[16];
	PVOID Reserved2[10];
	UNICODE_STRING ImagePathName;
	UNICODE_STRING CommandLine;
} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

typedef struct _PEB
{
	BOOLEAN                         InheritedAddressSpace;
	BOOLEAN                         ReadImageFileExecOptions;
	BOOLEAN                         BeingDebugged;
	BOOLEAN                         BitField;
	HANDLE                          Mutant;
	PVOID                           ImageBaseAddress;
	PPEB_LDR_DATA                   Ldr;
	PRTL_USER_PROCESS_PARAMETERS    ProcessParameters;
	PVOID                           SubSystemData;
	PVOID                           ProcessHeap;
	PVOID                           FastPebLock;
} PEB, * PPEB;

#include "peb.h"
#include "file.h"
#include "translation.h"