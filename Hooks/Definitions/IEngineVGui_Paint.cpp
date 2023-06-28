#include "../Hooks.h"

#include "../../Features/ESP/ESP.h"

DEFINE_HOOK(IEngineVGui_Paint, void, __fastcall, void* ecx, void* edx, int mode)
{
	Func.Original<FN>()(ecx, edx, mode);

	if (mode & PAINT_UIPANELS)
	{
		H::Draw.UpdateMatrix();

		I::MatSystemSurface->StartDrawing();
		{
			if (g_Globals.m_bIsInGame && !g_Globals.m_bIsGameUIVisible)
			{
				C_CSPlayer* pLocal = Util::CSPlayerByIndex(g_Globals.m_nLocalIndex);

				if (pLocal)
				{
					F::ESP.Render(pLocal);
				}
			}

			H::Draw.String(EFonts::DEBUG, 5, 5, { 204, 204, 204, 255 }, TXT_DEFAULT, L"CSS-Internal by whydoIhax - unknowncheats.me");
		}
		I::MatSystemSurface->FinishDrawing();
	}
}