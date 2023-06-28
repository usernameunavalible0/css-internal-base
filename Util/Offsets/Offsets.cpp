#include "Offsets.h"

#define GETPATT(x, mod, patt) x = U::Pattern.Find(mod, patt); XASSERT(x == 0x0)

void CUtil_Offsets::Initialize()
{
	GETPATT(m_dwClientModeShared_CreateMove, "client.dll", "55 8B EC E8 ? ? ? ? 8B C8 85 C9 75 06");
	GETPATT(m_dwC_BasePlayer_CalcPlayerView, "client.dll", "55 8B EC 83 EC 18 53 56 8B F1 8B");
	GETPATT(m_dwC_BaseEntity_SetPredictionRandomSeed, "client.dll", "55 8B EC 8B 45 08 85 C0 75 0C");
	GETPATT(m_dwC_BasePlayer_UsingStandardWeaponsInVehicle, "client.dll", "56 57 8B F9 8B B7 ? ? ? ? 83 FE FF 74 4D");
	GETPATT(m_dwC_BasePlayer_UpdateButtonState, "client.dll", "55 8B EC 8B 81 ? ? ? ? 8B D0");
	GETPATT(m_dwPredictionPlayer, "client.dll", "89 3D ? ? ? ? F3 0F");

	GETPATT(m_dwGlobalVars, "engine.dll", "A1 ? ? ? ? 8B 11 68");

	GETPATT(m_dwStartDrawing, "vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14");
	GETPATT(m_dwFinishDrawing, "vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00");
}