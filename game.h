#pragma once

#include <Windows.h>
#include "mathutils.h"

enum AreaId
{
	UNDEAD_BURG		= 1,
	FIRELINK_SHRINE = 2,
	CATACOMBS		= 6,
	UNDEAD_ASYLUM	= 16
};

struct LocationAndRotation
{
	Vec3D rot;		// 0x00
	char unk0[0x4];	// 0x0C
	Vec3D pos;		// 0x10
};

struct Positioning
{
	char unk0[0x1C];
	LocationAndRotation* locAndRot;	// 0x1C
};

struct Entity
{
	char unk0[0x04];
	unsigned int entityId;			// 0x04
	char unk1[0x14];
	unsigned int currentAreaId;		// 0x1C
	unsigned int previousAreaId;	// 0x20
	char unk2[0x04];				// 0x24
	Positioning* positioning;		// 0x28
};

struct EntityContainer {
	Entity* entity;					// 0x00
	char unk0[0x04];
	unsigned int currentAreaId;		// 0x08
	unsigned int previousAreaId;	// 0x0C
	char unk1[0x04];
	unsigned int flag;				// 0x14
	char unk2[0x08];
};

struct Player : Entity
{
};

struct Area
{
	char unk0[0x3C];
	unsigned int entitiesNum;	// 0x3C
	EntityContainer* entities;	// 0x40
	char unk1[0x54];			
	// 0x98
};

struct DialogueState
{
	char unk0[0x10];
	unsigned int interactionId;		// 0x10
	int currentDialogueStateId;		// 0x14
	int currentDialogueIncrement;	// 0x18
};

struct Interaction2
{
	char unk0[0x08];
	unsigned int interactionId;	// 0x08
	char unk1[0x04];
	DialogueState* dialogue;
};

struct Interaction
{
	char unk0[0x88];
	Interaction2* ptr;
};

struct Item
{
	Item* next;				// 0x00
	Item* prev;				// 0x04
	char unk0[0x08];
	unsigned int itemId;	// 0x10
	char unk1[0x0C];
	Vec3D pos;				// 0x20
	char unk2[0x0C];
	unsigned char flags;	// 0x38
};

struct Items
{
	char unk0[0x2C];
	Item* firstItem;		// 0x2C
	Item* lastItem;			// 0x30
};

struct Game
{
	char unk0[0x1C];
	unsigned int areasNum;	// 0x1C
	Area* areas;			// 0x20
	char unk1[0x18];		// 0x24
	Player* player;			// 0x3C
};

struct Camera
{
	char unk0[0x10];
	Vec3D right;		// 0x10
	char unk1[0x04];
	Vec3D up;			// 0x20
	char unk2[0x04];
	Vec3D forward;		// 0x30
	char unk3[0x4];
	Vec3D pos;			// 0x40
};

struct Actionable
{
	char unk0[0x0c];
	unsigned int entityId;	// 0x0C
	char unk1[0x04];
	unsigned int flags1;	// 0x14
	unsigned int flags2;	// 0x18
	char unk2[0x18];
	unsigned int type;		// 0x34
	char unk3[0x0C];
	void* ptr;				// 0x44
	char unk4[0x24];
	float posX;				// 0x6C
	char unk5[0xC];
	float posY;				// 0x7C
	char unk6[0xC];
	float posZ;				// 0x8C
};

class Hooks
{
	static bool bHooked;
	static HMODULE hModule;

public:
	static void Initialize();
	static void Release();

	static void nCreatePlayer();
	static void nDestroyPlayer();
	static void nInteractionLoop();
	static void nUpdateCamera();
	static void nUpdateActionable();
};

class GameUtils
{
public:
	static int InteractionIdToEntityId(unsigned int interactionId);
	static Entity* EntityIdToPtr(int entityId);
	static int InteractionIdToScriptId(unsigned int interactionId);
	static unsigned int BonfireLevel(unsigned int scriptId);
};