//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once

#include <string>
#include <vector>
#include <WS2tcpip.h>
#include <map>
#include <chrono>

#include "Logger.h"


namespace Utility_Network
{
	enum class EndpointState
	{
		Client =1,
		Server,
		NONE = 9
	};

	class Endpoint
	{
	public:
		Endpoint();

		void Initialize(const char* ip, unsigned short port, EndpointState state);

		std::string GetHostName() const { return m_HostName; };

		in_addr GetIPAddress() const { return m_IPAddress; };
		std::string GetIPAsString() const { return m_IPAsString; };

		unsigned short GetPort() const { return m_Port; };

		std::vector<uint8_t> GetIPBytes() const { return m_IPBytes; };

		sockaddr_in GetSocketAddress() const { return m_SocketAddress; };

		void AddItemToMessageManager(int value);

		void SearchForItem(int value);

		Utility_Network::EndpointState GetEndpointState();

	private:

		std::string m_HostName;

		in_addr m_IPAddress;
		std::string m_IPAsString;

		unsigned short m_Port;

		std::vector<uint8_t> m_IPBytes;

		sockaddr_in m_SocketAddress;

		EndpointState m_State;

		std::map<int, time_t> m_MessageManager;

	};
}