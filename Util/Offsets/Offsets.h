#pragma once

#include "../Pattern/Pattern.h"

class CUtil_Offsets
{
public:
	void Initialize();

public:
	DWORD m_dwClientModeShared_CreateMove = 0x0;
	DWORD m_dwC_BasePlayer_CalcPlayerView = 0x0;
	DWORD m_dwC_BaseEntity_SetPredictionRandomSeed = 0x0;
	DWORD m_dwC_BasePlayer_UsingStandardWeaponsInVehicle = 0x0;
	DWORD m_dwC_BasePlayer_UpdateButtonState = 0x0;
	DWORD m_dwPredictionPlayer = 0x0;
	DWORD m_dwGlobalVars = 0x0;
	DWORD m_dwStartDrawing = 0x0;
	DWORD m_dwFinishDrawing = 0x0;
};

namespace U { inline CUtil_Offsets Offsets; }