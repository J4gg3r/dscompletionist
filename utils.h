#ifndef __UTILS_H__
#define __UTILS_H__

#include <windows.h>

class Utils
{
	static BOOL dataCompare(BYTE* data, BYTE* pattern, BYTE* mask);

public:
	static DWORD findPattern(DWORD address, DWORD len, BYTE* pattern, BYTE* mask);
	static bool patchCode(LPVOID address, char* code, int length, char* oldCode = NULL);
	static VOID crash();
};

#endif