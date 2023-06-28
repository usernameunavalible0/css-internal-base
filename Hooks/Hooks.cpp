#include "Hooks.h"

void CGlobal_Hooks::Initialize()
{
	XASSERT(MH_Initialize() != MH_STATUS::MH_OK);

	Hooks::ClientModeShared_CreateMove::Initialize();
	Hooks::IEngineVGui_Paint::Initialize();
	Hooks::IBaseClientDLL_FrameStageNotify::Initialize();
	Hooks::IBaseClientDLL_LevelInitPostEntity::Initialize();
	Hooks::IBaseClientDLL_LevelShutdown::Initialize();
	Hooks::CPrediction_RunCommand::Initialize();
	Hooks::CBasePlayer_CalcPlayerView::Initialize();

	XASSERT(MH_EnableHook(MH_ALL_HOOKS) != MH_STATUS::MH_OK);

	I::Cvar->ConsoleColorPrintf({ 15, 150, 15, 255 }, "[CSS-Internal] CGlobal_Hooks::Initialize() finished!\n");
}

void CGlobal_Hooks::Uninitialize()
{
	XASSERT(MH_Uninitialize() != MH_STATUS::MH_OK);

	I::Cvar->ConsoleColorPrintf({ 15, 150, 15, 255 }, "[CSS-Internal] CGlobal_Hooks::Uninitialize() finished!\n");
}
