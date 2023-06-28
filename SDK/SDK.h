#pragma once

#include "DrawManager/DrawManager.h"

namespace Util
{
	inline Color GetHealthColor(const int nHealth, const int nMaxHealth)
	{
		if (nHealth > nMaxHealth)
			return { 15, 150, 150, 255 };

		const int nHP = U::Math.Max(0, U::Math.Min(nHealth, nMaxHealth));

		const unsigned int nR = static_cast<unsigned int>(U::Math.Min((510 * (nMaxHealth - nHP)) / nMaxHealth, 200));
		const unsigned int nG = static_cast<unsigned int>(U::Math.Min((510 * nHP) / nMaxHealth, 200));

		return { static_cast<byte>(nR), static_cast<byte>(nG), 0, 255 };
	}

	inline Color GetTeamColor(const int nTeam)
	{
		if (nTeam == 2)
			return Color(240, 90, 90, 255);
		else if (nTeam == 3)
			return Color(150, 200, 255, 255);
		else
			return Color(245, 229, 196, 255);
	}

	inline void MakeSafeName(const char* oldName, char* newName, int newNameBufSize)
	{
		assert(newNameBufSize >= sizeof(newName[0]));

		int newpos = 0;

		for (const char* p = oldName; *p != 0 && newpos < newNameBufSize - 1; p++)
		{
			//check for a '#' char at the beginning
			if (p == oldName && *p == '#')
			{
				newName[newpos] = '*';
				newpos++;
			}
			else if (*p == '%')
			{
				// remove % chars
				newName[newpos] = '*';
				newpos++;
			}
			else if (*p == '&')
			{
				//insert another & after this one
				if (newpos + 2 < newNameBufSize)
				{
					newName[newpos] = '&';
					newName[newpos + 1] = '&';
					newpos += 2;
				}
			}
			else
			{
				newName[newpos] = *p;
				newpos++;
			}
		}
		newName[newpos] = 0;
	}

	inline const char* SafeName(const char* oldName)
	{
		static char safeName[MAX_PLAYER_NAME_LENGTH * 2 + 1];
		MakeSafeName(oldName, safeName, sizeof(safeName));

		return safeName;
	}

	template<typename T>
	inline T EntityAs(int entindex)
	{
		IClientEntity* pEntity = EntityByIndex(entindex);

		return pEntity ? pEntity->As<T>() : nullptr;
	}
}