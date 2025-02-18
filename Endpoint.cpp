//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once

#pragma comment(lib, "Ws2_32.lib")

#include "Endpoint.h"

namespace Utility_Network
{
	Endpoint::Endpoint()
		:m_HostName({}), m_IPAddress({}), m_IPAsString({}), m_Port(0), m_IPBytes({}), m_SocketAddress({}), m_State(Utility_Network::EndpointState::NONE)
	{

	}

	void Endpoint::Initialize(const char* ip, unsigned short port, EndpointState state)
	{
		m_Port = port;
		m_State = state;

		int checkIPConversion = inet_pton(AF_INET, ip, &m_IPAddress);

		if (checkIPConversion == 1)
		{
			if (m_IPAddress.S_un.S_addr != INADDR_NONE)
			{
				m_IPAsString = ip;
				m_HostName = ip;

				m_IPBytes.resize(sizeof(ULONG));
				memcpy(&m_IPBytes[0], &m_IPAddress.S_un.S_addr, sizeof(ULONG));

				Utility_General::Logger::Log("Endpoint Initialized", Utility_General::LogLevel::LevelInfo);

				m_SocketAddress.sin_family = AF_INET;
				memcpy(&m_SocketAddress.sin_addr, &m_IPBytes[0], sizeof(ULONG));
				m_SocketAddress.sin_port = htons(m_Port);
			}
		}
	}

	void Endpoint::AddItemToMessageManager(int value)
	{
		std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		m_MessageManager.insert({ value, currentTime });
	}

	void Endpoint::SearchForItem(int value)
	{
		std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		auto it = m_MessageManager.find(value);

		if (it != m_MessageManager.end())
		{
			std::time_t messageTime = it->second;
			if (currentTime - messageTime > 1)
			{
				Utility_General::Logger::Log("UNSTABLE CONNECTION", Utility_General::LogLevel::LevelWarning);
			}
			m_MessageManager.erase(it);
		}
	}

	Utility_Network::EndpointState Endpoint::GetEndpointState()
	{
		return m_State;
	}
}