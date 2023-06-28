#include "EnginePrediction.h"

void CFeatures_EnginePrediction::Start(CUserCmd* cmd)
{
	if (!I::MoveHelper)
		return;

	C_CSPlayer* pLocal = Util::CSPlayerByIndex(g_Globals.m_nLocalIndex);

	if (!pLocal)
		return;

	cmd->random_seed = (MD5_PseudoRandom(cmd->command_number) & INT_MAX);

	pLocal->SetCurrentCommand(cmd);
	C_BaseEntity::SetPredictionRandomSeed(cmd);
	C_BaseEntity::SetPredictionPlayer(pLocal);

	m_fOldCurrentTime = I::GlobalVars->curtime;
	m_fOldFrameTime = I::GlobalVars->frametime;
	m_nOldTickCount = I::GlobalVars->tickcount;

	const int nOldFlags = pLocal->m_fFlags();
	const int nOldTickBase = pLocal->m_nTickBase();
	const bool bOldIsFirstPrediction = I::ClientPrediction->m_bFirstTimePredicted;
	const bool bOldInPrediction = I::ClientPrediction->m_bInPrediction;

	const int nServerTicks = GetTickbase(pLocal, cmd);

	I::GlobalVars->curtime = TICKS_TO_TIME(nServerTicks);
	I::GlobalVars->frametime = (I::ClientPrediction->m_bEnginePaused ? 0.0f : TICK_INTERVAL);
	I::GlobalVars->tickcount = nServerTicks;

	I::ClientPrediction->m_bFirstTimePredicted = false;
	I::ClientPrediction->m_bInPrediction = true;

	I::GameMovement->StartTrackPredictionErrors(pLocal);

	if (cmd->weaponselect != 0)
	{
		C_BaseCombatWeapon* pWeapon = Util::EntityAs<C_BaseCombatWeapon*>(cmd->weaponselect);

		if (pWeapon)
			pLocal->SelectItem(pWeapon->GetName(), cmd->weaponsubtype);
	}

	if (cmd->impulse)
	{
		if (!pLocal->GetClientVehicle() || pLocal->UsingStandardWeaponsInVehicle())
			pLocal->m_nImpulse() = cmd->impulse;
	}

	pLocal->UpdateButtonState(cmd->buttons);

	I::ClientPrediction->SetLocalViewAngles(cmd->viewangles);

	I::ClientPrediction->SetupMove(pLocal, cmd, I::MoveHelper, &m_MoveData);
	I::GameMovement->ProcessMovement(pLocal, &m_MoveData);
	I::ClientPrediction->FinishMove(pLocal, cmd, &m_MoveData);

	pLocal->m_nTickBase() = nOldTickBase;
	pLocal->m_fFlags() = nOldFlags;

	I::ClientPrediction->m_bInPrediction = bOldInPrediction;
	I::ClientPrediction->m_bFirstTimePredicted = bOldIsFirstPrediction;
}

void CFeatures_EnginePrediction::Finish()
{
	if (!I::MoveHelper)
		return;

	C_CSPlayer* pLocal = Util::CSPlayerByIndex(g_Globals.m_nLocalIndex);

	if (!pLocal)
		return;

	I::GameMovement->FinishTrackPredictionErrors(pLocal);

	I::GlobalVars->curtime = m_fOldCurrentTime;
	I::GlobalVars->frametime = m_fOldFrameTime;
	I::GlobalVars->tickcount = m_nOldTickCount;

	pLocal->SetCurrentCommand(nullptr);
	C_BaseEntity::SetPredictionRandomSeed(nullptr);
	C_BaseEntity::SetPredictionPlayer(nullptr);
}

int CFeatures_EnginePrediction::GetTickbase(C_CSPlayer* pLocal, CUserCmd* cmd)
{
	static int       s_nTick = 0;
	static CUserCmd* s_pLastCmd = nullptr;

	if (cmd)
	{
		if (!s_pLastCmd || s_pLastCmd->hasbeenpredicted)
			s_nTick = pLocal->m_nTickBase();
		else
			s_nTick++;

		s_pLastCmd = cmd;
	}

	return s_nTick;
}
