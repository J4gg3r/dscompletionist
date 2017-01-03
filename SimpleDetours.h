#ifndef __SIMPLEDETOURS_H__
#define __SIMPLEDETOURS_H__

#include <windows.h>

#pragma comment(lib, "SimpleDetours.lib")

PVOID DetourFunction(PBYTE pOrig, PBYTE pDetour);
PVOID DetourFunction(PBYTE pOrig, PBYTE pDetour, SIZE_T bytesToWrite);
VOID  DetourRemove(PBYTE pTrampoline);

#endif
