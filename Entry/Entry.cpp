#include "Entry.h"

void CGlobal_Entry::Load()
{
	while (!GetModuleHandleW(L"mss32.dll"))
		Sleep(100);

	U::Offsets.Initialize();

	//Interfaces
	{
		I::BaseClientDLL = U::Interface.Get<IBaseClientDLL*>("client.dll", "VClient017");
		I::ClientEntityList = U::Interface.Get<IClientEntityList*>("client.dll", "VClientEntityList003");
		I::GameMovement = U::Interface.Get<IGameMovement*>("client.dll", "GameMovement001");
		I::ClientPrediction = U::Interface.Get<CPrediction*>("client.dll", "VClientPrediction001");

		I::EngineClient = U::Interface.Get<IVEngineClient*>("engine.dll", "VEngineClient014");
		I::EngineVGui = U::Interface.Get<IEngineVGui*>("engine.dll", "VEngineVGui001");
		I::EngineTrace = U::Interface.Get<IEngineTrace*>("engine.dll", "EngineTraceClient003");
		I::RenderView = U::Interface.Get<IVRenderView*>("engine.dll", "VEngineRenderView014");
		I::ModelRender = U::Interface.Get<IVModelRender*>("engine.dll", "VEngineModel016");
		I::GameEventManager = U::Interface.Get<IGameEventManager2*>("engine.dll", "GAMEEVENTSMANAGER002");

		I::StudioRender = U::Interface.Get<IStudioRender*>("studiorender.dll", "VStudioRender025");

		I::MatSystemSurface = U::Interface.Get<IMatSystemSurface*>("vguimatsurface.dll", "VGUI_Surface030");

		I::Cvar = U::Interface.Get<ICvar*>("vstdlib.dll", "VEngineCvar004");

		//Other shenanigans
		{
			I::GlobalVars = *reinterpret_cast<CGlobalVarsBase**>(U::Offsets.m_dwGlobalVars + 0x8);
			XASSERT(I::GlobalVars == nullptr);

			I::PredictionPlayer = *reinterpret_cast<C_BasePlayer***>(U::Offsets.m_dwPredictionPlayer + 0x2);
			XASSERT(I::PredictionPlayer == nullptr);
		}
	}

	H::Draw.Initialize();

	if (I::EngineClient->IsInGame())
		g_Globals.m_nLocalIndex = I::EngineClient->GetLocalPlayer();

	G::Hooks.Initialize();

	I::Cvar->ConsoleColorPrintf({ 15, 150, 15, 255 }, "[CSS-Internal] CGlobal_Entry::Load() finished!\n");
}

void CGlobal_Entry::Unload()
{
	G::Hooks.Uninitialize();

	Sleep(100);

	H::Draw.Uninitialize();

	Sleep(100);

	I::Cvar->ConsoleColorPrintf({ 15, 150, 15, 255 }, "[CSS-Internal] CGlobal_Entry::Unload() finished!\n");
}
