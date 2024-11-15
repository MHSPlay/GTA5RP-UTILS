#pragma once

namespace config
{

	namespace afk_bypass
	{
		inline bool bEnabled = false;
		inline bool bAutoWheel = false;
	};

	namespace fast_loot
	{
		inline bool bEnabled = false;
		inline int  iKey = 0;

	};

	namespace harbor
	{
		inline bool bEnabled = false;
		inline int  iKeyMode = 1;
		inline int  iKey = 0;
	};

	namespace sewing
	{
		inline bool bEnabled = false;
		inline int  iKeyMode = 1;
		inline int  iKey = 0;

		inline int iDelay = 250;
		inline int iDelay2 = 250;
		inline int iDelay3 = 250;

	};

}