#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include "game.h"
#include "box.h"

class Radar
{
	bool m_display;
	bool m_inGame;
	std::list<Vec3D> m_chestPositions;
	std::list<Vec3D> m_bonfirePositions;

	void DrawCorpseBoxes(IDirect3DDevice9* pDevice, ID3DXLine* pLine, unsigned int width, unsigned int height);
	void DrawChestBoxes(IDirect3DDevice9* pDevice, ID3DXLine* pLine, unsigned int width, unsigned int height);
	void DrawBonfireBoxes(IDirect3DDevice9* pDevice, ID3DXLine* pLine, unsigned int width, unsigned int height);
	void DrawInfoText(ID3DXFont* pFont, unsigned int width, unsigned int height);
	void DrawBox(ID3DXLine* pLine, Box* box, D3DCOLOR color, unsigned int width, unsigned int height);

public:
	Radar();

	void ToggleDisplay();
	void SetInGame(bool enable);
	void AddChestPosition(float x, float y, float z);
	void AddBonfirePosition(float x, float y, float z);
	void Draw(IDirect3DDevice9* pDevice, ID3DXFont* pFont, ID3DXLine* pLine, unsigned int width, unsigned int height);
};

extern Radar radar;