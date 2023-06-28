#include "../Hooks.h"

#include "../../Features/EnginePrediction/EnginePrediction.h"
#include "../../Features/Misc/Misc.h"
#include "../../Features/NoSpread/NoSpread.h"

DEFINE_HOOK(ClientModeShared_CreateMove, bool, __fastcall, void* ecx, void* edx, float input_sample_frametime, CUserCmd* cmd)
{
	if (!cmd || !cmd->command_number)
		return Func.Original<FN>()(ecx, edx, input_sample_frametime, cmd);

	C_CSPlayer* pLocal = Util::CSPlayerByIndex(g_Globals.m_nLocalIndex);

	if (pLocal && pLocal->IsAlive())
	{
		C_WeaponCSBase* pWeapon = pLocal->GetActiveCSWeapon();

		if (pWeapon)
		{
			F::EnginePrediction.Start(cmd);
			{
				F::NoSpread.Run(pLocal, pWeapon, cmd);
			}
			F::EnginePrediction.Finish();
		}

		F::Misc.Run(pLocal, cmd);
	}

	return false;
}