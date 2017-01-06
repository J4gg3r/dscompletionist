#pragma once

#include "game.h"
#include "radar.h"
#include "SimpleDetours.h"
#include "utils.h"
#include "logger.h"

BYTE gamePtrPattern[] = "\xa1\xcc\xcc\xcc\xcc\x3b\xc3\x74\x05\x8b\x70\x3c";
BYTE gamePtrMask[] = "x????xxxxxxx";

BYTE itemsPtrPattern[] = "\x8b\x1d\xcc\xcc\xcc\xcc\x83\xec\x08";
BYTE itemsPtrMask[] = "xx????xxx";

BYTE createPlayerPattern[] = "\x55\x8b\xec\x83\xe4\xf8\x6a\xff\x68\xcc\xcc\xcc\xcc\x64\xa1\x00\x00\x00\x00\x50\x83\xec\x0c\x53\x56\xa1\xcc\xcc\xcc\xcc\x33\xc4\x50\x8d\x44\x24\x18\x64\xa3\x00\x00\x00\x00\x8b\x47";
BYTE createPlayerMask[] = "xxxxxxxxx????xxxxxxxxxxxxx????xxxxxxxxxxxxxxx";

BYTE destroyPlayerPattern[] = "\x51\x53\x55\x56\x8b\xb7\xcc\xcc\xcc\xcc\x33\xdb";
BYTE destroyPlayerMask[] = "xxxxxx????xx";

BYTE interactionLoopPattern[] = "\xf3\x0f\x10\x69\xcc\x80\x7a\xcc\x00";
BYTE interactionLoopMask[] = "xxxx?xx?x";

BYTE interactionIdToEntityIdPattern[] = "\x53\x8b\x59\x70\x55\x8b\x6c\x24\x0c";
BYTE interactionIdToEntityIdMask[] = "xxxxxxxxx";

BYTE entityIdToPtrPattern[] = "\x8b\xca\xc1\xe9\x0e\x83\xe1\x3f\x33\xc0";
BYTE entityIdToPtrMask[] = "xxxxxxxxxx";

BYTE interactionIdToScriptIdPattern[] = "\x8b\x48\x10\x56\x8b\x35\xcc\xcc\xcc\xcc\x57\x51";
BYTE interactionIdToScriptIdMask[] = "xxxxxx????xx";

BYTE bonfireLevelPattern[] = "\x51\xa1\xcc\xcc\xcc\xcc\x8b\x80\xcc\xcc\xcc\xcc\x56\x50";
BYTE bonfireLevelMask[] = "xx????xx????xx";

BYTE updateCameraPattern[] = "\x55\x8b\xec\x83\xe4\xf0\x8b\x15\xcc\xcc\xcc\xcc\x81\xec";
BYTE updateCameraMask[] = "xxxxxxxx????xx";

BYTE updateActionablePattern[] = "\xc1\xe1\x06\x03\x48\x40\x0f\x84";
BYTE updateActionableMask[] = "xxxxxxxx";

Game** ppGame;
Items** ppItems;
Camera* pCamera = NULL;

typedef void (WINAPI *createPlayer_t)();
typedef void (WINAPI *destroyPlayer_t)();
typedef void (*interactionLoop_t)();
typedef int (__fastcall *interactionIdToEntityId_t)(Game* pGame, int _edx, unsigned int interactionId);
typedef unsigned int (__cdecl *bonfireLevel_t)(unsigned int scriptId);
typedef void (*updateCamera_t)();

createPlayer_t origCreatePlayer;
createPlayer_t pCreatePlayer;

destroyPlayer_t origDestroyPlayer;
destroyPlayer_t pDestroyPlayer;

interactionLoop_t origInteractionLoop;
interactionLoop_t pInteractionLoop;

updateCamera_t origUpdateCamera;
updateCamera_t pUpdateCamera;

interactionIdToEntityId_t pInteractionIdToEntityId;
DWORD pEntityIdToPtr; // esi, edx params
DWORD pInteractionIdToScriptId; // eax param

bonfireLevel_t pBonfireLevel;

DWORD origUpdateActionable;
DWORD pUpdateActionable;

bool Hooks::bHooked = false;
HMODULE Hooks::hModule = NULL;

void Hooks::Initialize()
{
	if (!bHooked)
	{
		add_log("Hooks::Initialize");

		hModule = GetModuleHandle(NULL);
		
		DWORD gamePtrAddr = Utils::findPattern((DWORD)hModule, 0xCCC000, gamePtrPattern, gamePtrMask);
		ppGame = *(Game***)(gamePtrAddr + 1);

		DWORD itemsPtrAddr = Utils::findPattern((DWORD)hModule, 0xCCC000, itemsPtrPattern, itemsPtrMask);
		ppItems = *(Items***)(itemsPtrAddr + 2);

		origCreatePlayer = (createPlayer_t) Utils::findPattern((DWORD)hModule, 0xCCC000, createPlayerPattern, createPlayerMask);
		origDestroyPlayer = (destroyPlayer_t) Utils::findPattern((DWORD)hModule, 0xCCC000, destroyPlayerPattern, destroyPlayerMask);
		origInteractionLoop = (interactionLoop_t) Utils::findPattern((DWORD)hModule, 0xCCC000, interactionLoopPattern, interactionLoopMask);
		pInteractionIdToEntityId = (interactionIdToEntityId_t) Utils::findPattern((DWORD) hModule, 0xCCC000, interactionIdToEntityIdPattern, interactionIdToEntityIdMask);
		pEntityIdToPtr = Utils::findPattern((DWORD) hModule, 0xCCC000, entityIdToPtrPattern, entityIdToPtrMask);
		pInteractionIdToScriptId = Utils::findPattern((DWORD) hModule, 0xCCC000, interactionIdToScriptIdPattern, interactionIdToScriptIdMask);
		pBonfireLevel = (bonfireLevel_t) Utils::findPattern((DWORD) hModule, 0xCCC000, bonfireLevelPattern, bonfireLevelMask);
		origUpdateCamera = (updateCamera_t) Utils::findPattern((DWORD) hModule, 0xCCC000, updateCameraPattern, updateCameraMask);
		origUpdateActionable = Utils::findPattern((DWORD)hModule, 0xCCC000, updateActionablePattern, updateActionableMask);

		add_log("ppGame: %x", ppGame);
		add_log("ppItems: %x", ppItems);
		add_log("CreatePlayer: %x", origCreatePlayer);
		add_log("DestroyPlayer: %x", origDestroyPlayer);
		add_log("InteractionLoop: %x", origInteractionLoop);
		add_log("InteractionIdToEntityId: %x", pInteractionIdToEntityId);
		add_log("EntityIdToPtr: %x", pEntityIdToPtr);
		add_log("InteractionIdToScriptId: %x", pInteractionIdToScriptId);
		add_log("BonfireLevel: %x", pBonfireLevel);
		add_log("UpdateCamera: %x", origUpdateCamera);
		add_log("UpdateActionable: %x", origUpdateActionable);

		pCreatePlayer = (createPlayer_t) DetourFunction((BYTE*) origCreatePlayer, (BYTE*) Hooks::nCreatePlayer);
		pDestroyPlayer = (destroyPlayer_t) DetourFunction((BYTE*) origDestroyPlayer, (BYTE*) Hooks::nDestroyPlayer);
		pInteractionLoop = (interactionLoop_t)DetourFunction((BYTE*) origInteractionLoop, (BYTE*) Hooks::nInteractionLoop);
		pUpdateCamera = (updateCamera_t)DetourFunction((BYTE*) origUpdateCamera, (BYTE*) Hooks::nUpdateCamera);
		pUpdateActionable = (DWORD) DetourFunction((BYTE*) origUpdateActionable, (BYTE*)Hooks::nUpdateActionable);

		bHooked = true;
	}
}

void Hooks::Release()
{
	if (bHooked)
	{
		add_log("Hooks::Release");

		DetourRemove((BYTE*) pCreatePlayer);
		DetourRemove((BYTE*) pDestroyPlayer);
		DetourRemove((BYTE*) pInteractionLoop);
		DetourRemove((BYTE*) pUpdateCamera);
		DetourRemove((BYTE*) pUpdateActionable);

		bHooked = false;
	}
}

void onCreatePlayer()
{
	radar.SetInGame(true);
}

__declspec(naked)
void Hooks::nCreatePlayer()
{
	__asm
	{
		pushad
		call onCreatePlayer
		popad
		jmp pCreatePlayer
	}
}

void onDestroyPlayer()
{
	radar.SetInGame(false);
}

__declspec(naked)
void Hooks::nDestroyPlayer()
{
	__asm
	{
		pushad
		call onDestroyPlayer
		popad
		jmp pDestroyPlayer
	}
}

void WINAPI onInteractionLoop(Interaction* interaction)
{
	unsigned int interactionId = interaction->ptr->interactionId;
	int scriptId = GameUtils::InteractionIdToScriptId(interactionId);
	if (scriptId > 0)
	{
		unsigned int bonfireLevel = GameUtils::BonfireLevel(scriptId);
		if (!bonfireLevel)
		{
			int entityId = GameUtils::InteractionIdToEntityId(interactionId);
			if (entityId > 0)
			{
				Entity* entity = GameUtils::EntityIdToPtr(entityId);
				Vec3D& pos = entity->positioning->locAndRot->pos;
				radar.AddBonfirePosition(pos.x, pos.y, pos.z);
			}
		}
	}
}

__declspec(naked)
void Hooks::nInteractionLoop()
{
	__asm
	{
		pushad
		mov edx, dword ptr [edx+4]
		push edx
		call onInteractionLoop
		popad
		jmp pInteractionLoop
	}
}

void WINAPI onUpdateCamera(Camera* camera)
{
	pCamera = camera;
}

__declspec(naked)
void Hooks::nUpdateCamera()
{
	__asm
	{
		pushad
		push dword ptr [esp+0x24]
		call onUpdateCamera
		popad
		jmp pUpdateCamera
	}
}

void WINAPI onUpdateActionable(Actionable* actionable)
{
	if (actionable->type == 0x11 && actionable->flags1 && !actionable->ptr)
	{
		radar.AddChestPosition(actionable->posX, actionable->posY, actionable->posZ);
	}
}

__declspec(naked)
void Hooks::nUpdateActionable()
{
	__asm
	{
		pushad
		shl ecx, 6
		add ecx, dword ptr[eax + 0x40]
		push ecx
		call onUpdateActionable
		popad
		jmp pUpdateActionable
	}
}

int GameUtils::InteractionIdToEntityId(unsigned int interactionId)
{
	return pInteractionIdToEntityId(*ppGame, 0, interactionId);
}

Entity* GameUtils::EntityIdToPtr(int entityId)
{
	Entity* result = NULL;
	Game* pGame = *ppGame;
	__asm
	{
		mov esi, pGame
		mov edx, entityId
		call pEntityIdToPtr
		mov result, eax
	}
	return result;
}

int GameUtils::InteractionIdToScriptId(unsigned int interactionId)
{
	unsigned int result = 0;
	__asm
	{
		push interactionId
		sub esp, 0x10
		mov eax, esp
		call pInteractionIdToScriptId
		add esp, 0x10
		mov result, eax
	}
	return result;
}

unsigned int GameUtils::BonfireLevel(unsigned int scriptId)
{
	return pBonfireLevel(scriptId);
}