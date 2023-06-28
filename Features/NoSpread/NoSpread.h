#pragma once

#include "../../SDK/SDK.h"

class CFeatures_NoSpread
{
public:
	void Run(C_CSPlayer* pLocal, C_WeaponCSBase* pWeapon, CUserCmd* cmd);

private:
	bool ShouldRun(C_WeaponCSBase* pWeapon, CUserCmd* cmd);
};

namespace F { inline CFeatures_NoSpread NoSpread; }