#pragma once
#include "../../SDK/SDK.h"

class CFeatures_Misc
{
public:
	void Run(C_CSPlayer* pLocal, CUserCmd* cmd);

private:
	void Bunnyhop(C_CSPlayer* pLocal, CUserCmd* cmd);
};

namespace F { inline CFeatures_Misc Misc; }