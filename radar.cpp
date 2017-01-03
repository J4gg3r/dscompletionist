#include <stdio.h>
#include "radar.h"

#define BOX_WIDTH 300
#define BOX_MARGIN 20

Radar radar;

extern Game** ppGame;
extern Items** ppItems;
extern Camera* pCamera;

Radar::Radar()
{
	m_display = false;
	m_inGame = false;
}

void Radar::ToggleDisplay()
{
	m_display = !m_display;
}

void Radar::SetInGame(bool enable)
{
	m_inGame = enable;
}

void Radar::AddChestPosition(float x, float y, float z)
{
	Vec3D v = {x, y, z};
	m_chestPositions.push_back(v);
}

void Radar::AddBonfirePosition(float x, float y, float z)
{
	Vec3D v = { x, y, z };
	m_bonfirePositions.push_back(v);
}

void Radar::Draw(IDirect3DDevice9* pDevice, ID3DXFont* pFont, ID3DXLine* pLine, unsigned int width, unsigned int height)
{
	if (m_inGame)
	{
		if (m_display)
		{
			DrawCorpseBoxes(pDevice, pLine, width, height);
			DrawChestBoxes(pDevice, pLine, width, height);
			DrawBonfireBoxes(pDevice, pLine, width, height);
		}
	}
	else
	{
		DrawInfoText(pFont, width, height);
	}

	m_chestPositions.clear();
	m_bonfirePositions.clear();
}

void Radar::DrawCorpseBoxes(IDirect3DDevice9* pDevice, ID3DXLine* pLine, unsigned int width, unsigned int height)
{
	Game* pGame = *ppGame;
	if (pGame)
	{
		Player* player = (*ppGame)->player;
		if (player)
		{
			Item* item = (*ppItems)->firstItem;
			while (item)
			{
				if (item->flags & 0x40)
				{
					Box box;
					box.InitWithCenter(item->pos);
					DrawBox(pLine, &box, D3DCOLOR_XRGB(255, 255, 255), width, height);
				}

				item = item->next;
			}
		}
	}
}

void Radar::DrawChestBoxes(IDirect3DDevice9* pDevice, ID3DXLine* pLine, unsigned int width, unsigned int height)
{
	std::list<Vec3D>::iterator it = m_chestPositions.begin();
	while (it != m_chestPositions.end())
	{
		Box box;
		box.InitWithCenter(*it);
		DrawBox(pLine, &box, D3DCOLOR_XRGB(0, 255, 0), width, height);
		it++;
	}
}

void Radar::DrawBonfireBoxes(IDirect3DDevice9* pDevice, ID3DXLine* pLine, unsigned int width, unsigned int height)
{
	std::list<Vec3D>::iterator it = m_bonfirePositions.begin();
	while (it != m_bonfirePositions.end())
	{
		Box box;
		box.InitWithCenter(*it);
		DrawBox(pLine, &box, D3DCOLOR_XRGB(255, 165, 0), width, height);
		it++;
	}
}

void Radar::DrawBox(ID3DXLine* pLine, Box* box, D3DCOLOR color, unsigned int width, unsigned int height)
{
	static float fov = 0.75f;

	D3DXVECTOR2 screenPos[8];
	bool draw = true;
	for (int i = 0; i < 8 && draw; i++)
	{
		draw = Math::WorldToScreen(box->vertices[i], pCamera->pos, pCamera->forward, pCamera->up, pCamera->right, fov, width, height, screenPos[i]);
	}

	D3DXVECTOR2 lines[16];
	lines[0] = screenPos[0];
	lines[1] = screenPos[1];
	lines[2] = screenPos[2];
	lines[3] = screenPos[3];
	lines[4] = screenPos[0];
	lines[5] = screenPos[4];
	lines[6] = screenPos[5];
	lines[7] = screenPos[6];
	lines[8] = screenPos[7];
	lines[9] = screenPos[4];
	lines[10] = screenPos[1];
	lines[11] = screenPos[5];
	lines[12] = screenPos[2];
	lines[13] = screenPos[6];
	lines[14] = screenPos[3];
	lines[15] = screenPos[7];

	if (draw)
	{
		pLine->SetWidth(2.0f);
		pLine->Draw(lines, 10, color);
		pLine->Draw(&lines[10], 2, color);
		pLine->Draw(&lines[12], 2, color);
		pLine->Draw(&lines[14], 2, color);
	}
}

void Radar::DrawInfoText(ID3DXFont* pFont, unsigned int width, unsigned int height)
{
	RECT fontRect;
	SetRect(&fontRect, width - 5, height - 20, width - 5, height);
	pFont->DrawText(NULL, "Dark Souls Completionist", -1, &fontRect, DT_NOCLIP | DT_LEFT | DT_RTLREADING, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}