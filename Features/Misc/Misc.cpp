#include "Misc.h"
#include "../Vars.h"

void CFeatures_Misc::Run(C_CSPlayer* pLocal, CUserCmd* cmd)
{
	if (Vars::Misc::Bunnyhop)
		Bunnyhop(pLocal, cmd);
}

void CFeatures_Misc::Bunnyhop(C_CSPlayer* pLocal, CUserCmd* cmd)
{
	static bool s_bState = false;

	if (cmd->buttons & IN_JUMP)
	{
		if (!s_bState && !(pLocal->m_fFlags() & FL_ONGROUND))
		{
			cmd->buttons &= ~IN_JUMP;
		}
		else if (s_bState)
		{
			s_bState = false;
		}
	}
	else if (!s_bState)
	{
		s_bState = true;
	}
}