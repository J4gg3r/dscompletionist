#include "utils.h"

BOOL Utils::dataCompare(BYTE* data, BYTE* pattern, BYTE* mask)
{
	for(; *mask; ++mask, ++data, ++pattern)
	{
		if(*mask == 'x' && *data != *pattern)
			return FALSE;
	}

	return (*pattern == NULL);
}

DWORD Utils::findPattern(DWORD address, DWORD len, BYTE* pattern, BYTE *mask)
{
	for(DWORD i = 0; i < len; i++)
	{
		if(Utils::dataCompare((BYTE*)(address + i), pattern, mask))
			return (DWORD)(address + i);
	}

	return 0;
}

bool Utils::patchCode(LPVOID address, char* code, int length, char* oldCode)
{
	DWORD oldProtect;

	if(!VirtualProtect(address, length, PAGE_EXECUTE_READWRITE, &oldProtect))
		return false;

	if(oldCode && memcpy_s(oldCode, length, address, length))
		return false;

	if(memcpy_s(address, length, code, length))
		return false;

	if(!VirtualProtect(address, length, oldProtect, NULL))
		return false;

	return true;
}

VOID Utils::crash()
{
	RaiseException(0xBAADC0DE, EXCEPTION_NONCONTINUABLE, 0, NULL);
}