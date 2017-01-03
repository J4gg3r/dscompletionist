#pragma once

#include <d3dx9.h>

class D3DUtils
{
public:
	static ID3DXFont* InitializeFont(IDirect3DDevice9* pDevice);
	static ID3DXLine* InitializeLine(IDirect3DDevice9* pDevice);
	static void ReleaseFont(ID3DXFont* pFont);
	static void ReleaseLine(ID3DXLine* pLine);

	static void GetWindowResolution(D3DPRESENT_PARAMETERS* pPresetParams, unsigned int* pWidth, unsigned int* pHeight);
};