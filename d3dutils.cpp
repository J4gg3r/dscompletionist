#include "d3dutils.h"

ID3DXFont* D3DUtils::InitializeFont(IDirect3DDevice9* pDevice)
{
	int m_nFontSize = 12;
	int nHeight;
	ID3DXFont* pFont;

	HDC hDC = GetDC(NULL);
	int nLogPixelsY = ::GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	nHeight = -m_nFontSize * nLogPixelsY / 72;
	D3DXCreateFont(pDevice,		     // D3D device
		nHeight,					 // Height
		0,							 // Width
		FW_BOLD,					 // Weight
		0,							 // MipLevels, 0 = autogen mipmaps
		FALSE,						 // Italic
		DEFAULT_CHARSET,			 // CharSet
		OUT_DEFAULT_PRECIS,			 // OutputPrecision
		ANTIALIASED_QUALITY,		 // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		"Monotype Corsiva",			 // pFaceName
		&pFont);					 // ppFont

	return pFont;
}

ID3DXLine* D3DUtils::InitializeLine(IDirect3DDevice9* pDevice)
{
	ID3DXLine* pLine;
	D3DXCreateLine(pDevice, &pLine);
	return pLine;
}

void D3DUtils::ReleaseFont(ID3DXFont* pFont)
{
	if (pFont)
	{
		pFont->Release();
	}
}

void D3DUtils::ReleaseLine(ID3DXLine* pLine)
{
	if (pLine)
	{
		pLine->Release();
	}
}

void D3DUtils::GetWindowResolution(D3DPRESENT_PARAMETERS* pPresetParams, unsigned int* pWidth, unsigned int* pHeight)
{
	RECT wndRect;
	GetWindowRect(pPresetParams->hDeviceWindow, &wndRect);
	*pWidth = wndRect.right - wndRect.left;
	*pHeight = wndRect.bottom - wndRect.top;
}