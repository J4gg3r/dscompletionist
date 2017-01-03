#include <windows.h>

#include "d3d9.h"
#include "logger.h"

tDirect3DCreate9 oDirect3DCreate9;
HMODULE g_hd3d9;

BOOL OpenMSD3D9()
{
	char szFileName[512];
	UINT ret;

	if(g_hd3d9 && oDirect3DCreate9)
		return TRUE;

	ret = GetSystemDirectory(szFileName, 256);
	if(ret <= 0)
	{
		return FALSE;
	}

	strcat_s(szFileName, sizeof(szFileName), "\\d3d9.dll");
	g_hd3d9 = LoadLibrary(szFileName);
	if(g_hd3d9 == NULL)
	{
		return FALSE;
	}

	oDirect3DCreate9 = (tDirect3DCreate9)GetProcAddress(g_hd3d9, "Direct3DCreate9");

	return oDirect3DCreate9 == NULL;
}

extern "C"
IDirect3D9 *APIENTRY Direct3DCreate9(UINT SDKVersion)
{
	OpenMSD3D9();
	IDirect3D9 *d3dint = oDirect3DCreate9(SDKVersion);

	if( d3dint != NULL )
	{
		hkIDirect3D9 *ret = new hkIDirect3D9(&d3dint);
		add_log("Direct3DCreate9(%i) succeeded...", SDKVersion);
		add_log("Hooked Direct3D9 interface: 0x%x -> 0x%x", ret->m_pD3Dint, ret);
	}
	else
		add_log("Direct3DCreate9(%i) failed...", SDKVersion);

	return d3dint;
}
