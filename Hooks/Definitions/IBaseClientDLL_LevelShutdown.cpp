#include "../../Hooks/Hooks.h"

DEFINE_HOOK(IBaseClientDLL_LevelShutdown, void, __fastcall, void* ecx, void* edx)
{
	g_Globals.m_bIsInGame = false;
	g_Globals.m_bIsGameUIVisible = true;

	g_Globals.m_nLocalIndex = -1;
	g_Globals.m_nMaxClients = -1;
	g_Globals.m_nMaxEntities = -1;

	Func.Original<FN>()(ecx, edx);
}