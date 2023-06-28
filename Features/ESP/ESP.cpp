#include "ESP.h"
#include "../Vars.h"

void CFeatures_ESP::Render(C_CSPlayer* pLocal)
{
	if (!Vars::ESP::Enabled)
		return;

	int x, y, w, h;
	for (int n = 1; n < (g_Globals.m_nMaxEntities + 1); n++)
	{
		if (n == g_Globals.m_nLocalIndex)
			continue;

		IClientEntity* pEntity = Util::EntityByIndex(n);

		if (!pEntity || pEntity->IsDormant())
			continue;

		ClientClass* pCC = pEntity->GetClientClass();

		if (!pCC)
			continue;

		switch (pCC->m_ClassID)
		{
		case ECSClientClass::CCSPlayer:
		{
			if (!Vars::ESP::Players::Enabled)
				break;

			C_CSPlayer* pPlayer = pEntity->As<C_CSPlayer*>();

			if (pPlayer->deadflag() || (Vars::ESP::Players::IgnoreTeam && pPlayer->InLocalTeam()))
				break;

			if (!GetDynamicBounds(pPlayer, x, y, w, h))
				break;

			const int nHealth = pPlayer->GetHealth();
			const int nMaxHealth = pPlayer->GetMaxHealth();

			const Color clrHealth = Util::GetHealthColor(nHealth, nMaxHealth);
			const Color clrTeam = Util::GetTeamColor(pPlayer->GetTeamNumber());

			const int nDrawX = x + (w + 3);
			int nDrawY = y;

			if (Vars::ESP::Players::Box)
			{
				H::Draw.OutlinedRect(x, y, w, h, clrTeam);
				
				//Outline
				H::Draw.OutlinedRect(x - 1, y - 1, w + 2, h + 2, COLOR_BLACK);

				//Inline
				H::Draw.OutlinedRect(x + 1, y + 1, w - 2, h - 2, COLOR_BLACK);
			}

			if (Vars::ESP::Players::HealthBar)
			{
				x -= 1;

				const float flMaxHealth = static_cast<float>(nMaxHealth);
				const float flHealth = U::Math.Clamp<float>(static_cast<float>(nHealth), 1.0f, flMaxHealth);

				static const int nWidth = 2;
				const int nHeight = (h + (flHealth < flMaxHealth ? 2 : 1));
				const int nHeight2 = (h + 1);

				const float ratio = (flHealth / flMaxHealth);
				H::Draw.Rect(static_cast<int>(((x - nWidth) - 2)), static_cast<int>((y + nHeight - (nHeight * ratio))), nWidth, static_cast<int>((nHeight * ratio)), clrHealth);
				H::Draw.OutlinedRect(static_cast<int>(((x - nWidth) - 2) - 1), static_cast<int>((y + nHeight - (nHeight * ratio)) - 1), nWidth + 2, static_cast<int>((nHeight * ratio) + 1), COLOR_BLACK);

				x += 1;
			}

			player_info_t pi;
			if (Vars::ESP::Players::Name && I::EngineClient->GetPlayerInfo(n, &pi))
			{
				wchar_t szName[MAX_PLAYER_NAME_LENGTH];
				Q_UTF8ToUTF16(Util::SafeName(pi.name), szName, MAX_PLAYER_NAME_LENGTH);

				H::Draw.String(EFonts::ESP_NAME,
					x + (w / 2),
					y - (H::Draw.GetFontHeight(EFonts::ESP_NAME) + 2),
					COLOR_GREY,
					TXT_CENTERX,
					szName);
			}

			break;
		}
		default: break;
		}
	}
}

bool CFeatures_ESP::GetDynamicBounds(C_BaseEntity* pEntity, int& x, int& y, int& w, int& h)
{
	Vector vPoints[8];
	U::Math.BuildTransformedBox(vPoints, pEntity->m_vecMins(), pEntity->m_vecMaxs(), pEntity->RenderableToWorldTransform());

	Vector2D flb, brt, blb, frt, frb, brb, blt, flt;

	if (H::Draw.WorldPosToScreenPos(vPoints[3], flb) && H::Draw.WorldPosToScreenPos(vPoints[5], brt)
		&& H::Draw.WorldPosToScreenPos(vPoints[0], blb) && H::Draw.WorldPosToScreenPos(vPoints[4], frt)
		&& H::Draw.WorldPosToScreenPos(vPoints[2], frb) && H::Draw.WorldPosToScreenPos(vPoints[1], brb)
		&& H::Draw.WorldPosToScreenPos(vPoints[6], blt) && H::Draw.WorldPosToScreenPos(vPoints[7], flt)
		&& H::Draw.WorldPosToScreenPos(vPoints[6], blt) && H::Draw.WorldPosToScreenPos(vPoints[7], flt))
	{
		const Vector2D arr[8] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float righ = flb.x;
		float bottom = flb.y;

		for (int n = 1; n < 8; n++)
		{
			if (left > arr[n].x)
				left = arr[n].x;

			if (top < arr[n].y)
				top = arr[n].y;

			if (righ < arr[n].x)
				righ = arr[n].x;

			if (bottom > arr[n].y)
				bottom = arr[n].y;
		}

		x = static_cast<int>(left);
		y = static_cast<int>(bottom);
		w = static_cast<int>((righ - left));
		h = static_cast<int>((top - bottom));

		return !(x > H::Draw.m_nScreenW || (x + w) < 0 || y > H::Draw.m_nScreenH || (y + h) < 0);
	}

	return false;
}
