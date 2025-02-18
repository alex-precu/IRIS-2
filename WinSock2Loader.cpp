//Code Owner: Alexandru Precupetu
//Restricted: No

#include <iostream>

#include "WinSock2Loader.h"

namespace Utility_Network
{
	bool WinSockLoader::EnableWinSock()
	{
		WSADATA wsaData;
		WORD wVersionRequested = MAKEWORD(2, 2);

		int checkWSAStartup = WSAStartup(wVersionRequested, &wsaData);

		if (checkWSAStartup != 0)
		{
			std::cout << "ERROR: FAILED TO ENABLE WINSOCK" << std::endl;
			return false;
		}
		else if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			std::cout << "ERROR: WRONG WINSOCK VERSION" << std::endl;
			return false;
		}
		else
		{
			return true;
		}
	}

	void WinSockLoader::DisableWinSock()
	{
		WSACleanup();
	}
}