//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef GLOBALVARS_BASE_H
#define GLOBALVARS_BASE_H

#ifdef _WIN32
#pragma once
#endif

#include "ICvar.h"

class CSaveRestoreData;

#define TICK_INTERVAL			(I::GlobalVars->interval_per_tick)

#define TIME_TO_TICKS( dt )		( (int)( 0.5f + (float)(dt) / TICK_INTERVAL ) )
#define TICKS_TO_TIME( t )		( TICK_INTERVAL *( t ) )
#define ROUND_TO_TICKS( t )		( TICK_INTERVAL * TIME_TO_TICKS( t ) )
#define TICK_NEVER_THINK		(-1)

class CGlobalVarsBase
{
public:

	CGlobalVarsBase(bool bIsClient);
	bool IsClient() const;
	int GetNetworkBase(int nTick, int nEntity);

public:
	float			realtime;
	int				framecount;
	float			absoluteframetime;
	float			curtime;
	float			frametime;
	int				maxClients;
	int				tickcount;
	float			interval_per_tick;
	float			interpolation_amount;
	int				simTicksThisFrame;
	int				network_protocol;
	CSaveRestoreData* pSaveData;

private:
	bool			m_bClient;
	int				nTimestampNetworkingBase;
	int				nTimestampRandomizeWindow;
};

inline int CGlobalVarsBase::GetNetworkBase(int nTick, int nEntity)
{
	int nEntityMod = nEntity % nTimestampRandomizeWindow;
	int nBaseTick = nTimestampNetworkingBase * (int)((nTick - nEntityMod) / nTimestampNetworkingBase);
	return nBaseTick;
}

inline CGlobalVarsBase::CGlobalVarsBase(bool bIsClient) :
	m_bClient(bIsClient),
	nTimestampNetworkingBase(100),
	nTimestampRandomizeWindow(32)
{
}

inline bool CGlobalVarsBase::IsClient() const
{
	return m_bClient;
}

namespace I { inline CGlobalVarsBase* GlobalVars = nullptr; }

#endif // GLOBALVARS_BASE_H