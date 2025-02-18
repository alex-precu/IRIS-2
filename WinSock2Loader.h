//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>

namespace Utility_Network
{
	/* WinsockLoader is used to enable and disable the Windows Winsock API*/
	class WinSockLoader
	{
	public:
		static bool EnableWinSock();
		static void DisableWinSock();
	};
}
