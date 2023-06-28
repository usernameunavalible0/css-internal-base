//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef ICLIENTENTITY_H
#define ICLIENTENTITY_H
#ifdef _WIN32
#pragma once
#endif


#include "iclientrenderable.h"
#include "iclientnetworkable.h"
#include "iclientthinkable.h"

struct Ray_t;
class CGameTrace;
typedef CGameTrace trace_t;
class CMouthInfo;
class IClientEntityInternal;
struct SpatializationInfo_t;

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable, public IClientThinkable
{
public:
	virtual void			Release(void) = 0;
	virtual const Vector&	GetAbsOrigin(void) const = 0;
	virtual const Vector&	GetAbsAngles(void) const = 0;
	virtual CMouthInfo*		GetMouth(void) = 0;
	virtual bool			GetSoundSpatialization(SpatializationInfo_t& info) = 0;

	template <typename T>
	inline T As()
	{
#ifdef _DEBUG
		return dynamic_cast<T>(this);
#else
		return static_cast<T>(this);
#endif
	}
};

namespace Util
{
	inline IClientEntity* EntityByIndex(const int entindex)
	{
		return I::ClientEntityList->GetClientEntity(entindex);
	}
}

#endif // ICLIENTENTITY_H