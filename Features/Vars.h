#pragma once

namespace Vars
{
	namespace ESP
	{
		inline bool Enabled = true;

		namespace Players
		{
			inline bool Enabled = true;
			inline bool IgnoreTeam = true;
			inline bool Box = true;
			inline bool HealthBar = true;
			inline bool Name = true;
		}
	}

	namespace Misc
	{
		inline bool Bunnyhop = true;
		inline bool NoSpread = true;
		inline bool NoRecoil = true;
	}

	namespace Visual
	{
		inline bool RemoveVisualRecoil = true;
	}
}