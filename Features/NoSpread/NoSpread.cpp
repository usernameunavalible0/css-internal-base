#include "NoSpread.h"
#include "../Vars.h"

void CFeatures_NoSpread::Run(C_CSPlayer* pLocal, C_WeaponCSBase* pWeapon, CUserCmd* cmd)
{
	static const auto s_pfRandomSeed = reinterpret_cast<void(_cdecl*)(unsigned)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomSeed"));
	static const auto s_pfRandomFloat = reinterpret_cast<float(_cdecl*)(float, float)>(GetProcAddress(GetModuleHandleW(L"vstdlib.dll"), "RandomFloat"));

	if (!ShouldRun(pWeapon, cmd))
		return;

	if (Vars::Misc::NoSpread)
	{
		Vector vForward, vRight, vUp, vFinal;

		s_pfRandomSeed((cmd->random_seed & 255) + 1);

		pWeapon->UpdateAccuracyPenalty();
		
		float fTheta0 = s_pfRandomFloat(0.0f, 2.0f * M_PI);
		float fRadius0 = s_pfRandomFloat(0.0f, pWeapon->GetSpread());
		float fTheta1 = s_pfRandomFloat(0.0f, 2.0f * M_PI);
		float fRadius1 = s_pfRandomFloat(0.0f, pWeapon->GetInaccuracy());

		float x0 = fRadius0 * cosf(fTheta0);
		float y0 = fRadius0 * sinf(fTheta0);
		float x1 = fRadius1 * cosf(fTheta1);
		float y1 = fRadius1 * sinf(fTheta1);

		float xSpread = x0 + x1;
		float ySpread = y0 + y1;

		U::Math.AngleVectors(cmd->viewangles, &vForward, &vRight, &vUp);

		Vector vSpreadAngles = vForward + (vRight * xSpread) + (vUp * ySpread);
		vSpreadAngles.Normalize();

		U::Math.VectorAngles(vSpreadAngles, vFinal);
		U::Math.ClampAngles(vFinal);

		Vector vNewAngles = (cmd->viewangles + (cmd->viewangles - vFinal));
		U::Math.ClampAngles(vNewAngles);

		cmd->viewangles = vNewAngles;
	}

	if (Vars::Misc::NoRecoil)
		cmd->viewangles -= pLocal->m_vecPunchAngle() * 2.f;
}

bool CFeatures_NoSpread::ShouldRun(C_WeaponCSBase* pWeapon, CUserCmd* cmd)
{
	if (!(cmd->buttons & IN_ATTACK))
		return false;

	if (!pWeapon->HasAnyAmmo())
		return false;

	switch (pWeapon->GetWeaponID())
	{
	case WEAPON_P228:
	case WEAPON_GLOCK:
	case WEAPON_SCOUT:
	case WEAPON_MAC10:
	case WEAPON_AUG:
	case WEAPON_FIVESEVEN:
	case WEAPON_UMP45:
	case WEAPON_SG550:
	case WEAPON_GALIL:
	case WEAPON_FAMAS:
	case WEAPON_USP:
	case WEAPON_AWP:
	case WEAPON_MP5NAVY:
	case WEAPON_M249:
	case WEAPON_M3:
	case WEAPON_M4A1:
	case WEAPON_TMP:
	case WEAPON_G3SG1:
	case WEAPON_DEAGLE:
	case WEAPON_SG552:
	case WEAPON_AK47:
	case WEAPON_P90:
		return true;
	default: break;
	}

	return false;
}
