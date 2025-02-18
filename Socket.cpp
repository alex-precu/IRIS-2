//Code Owner: Alexandru Precupetu
//Restricted: No

#include "Socket.h"

namespace Utility_Network
{
	Socket::Socket(SOCKET socket)
		:m_Socket(socket), m_Endpoint({}), m_IsConnected(false),m_NumberOfConnections(1)
	{

	}

	//Wrapper over Winsock's scoket() function, sets basic socket options
	Utility_General::ErrorCheck Socket::InitSocket(const char* ip, unsigned int port, Utility_Network::EndpointState state)
	{

//#ifndef NDEBUG
//		std::cout << __FUNCSIG__ << std::endl;
//#endif

		if (m_Socket != INVALID_SOCKET)
		{
			return Utility_General::ErrorCheck(true, "ERROR: SOCKET ALREADY CREATED");
		}

		m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

		if (m_Socket == INVALID_SOCKET)
		{
			return Utility_General::ErrorCheck(true, "ERROR: UNABLE TO INITIALIZE SOCKET");
		}

		Utility_General::ErrorCheck err = SetupSocket(SocketSettings::TCP_NoDelay, TRUE);

		if (err.IsFailed())
		{
			Utility_General::Logger::Log(err.GetErrorCheckDescription(), Utility_General::LogLevel::LevelError);
			return Utility_General::ErrorCheck(true, err.GetErrorCheckDescription());
		}
		else
		{
			m_Endpoint.Initialize(ip, port, state);

			Utility_General::Logger::Log("Socket Created", Utility_General::LogLevel::LevelInfo);
			return Utility_General::ErrorCheck(false);
		}

	}

	Utility_General::ErrorCheck Socket::CloseSocket()
	{
		if (m_Socket == INVALID_SOCKET)
		{
			return Utility_General::ErrorCheck(true, "ERROR: CANNOT CLOSE INVALID SOCKET");
		}

		//closesocket() is a WinSock function that returns 0 if no error occurs
		int checkCloseSocket = closesocket(m_Socket);
		if (checkCloseSocket != 0)
		{
			return Utility_General::ErrorCheck(true, "ERROR: SOCKET COULD NOT B E CLOSED");
		}
		m_Socket = INVALID_SOCKET;

		Utility_General::Logger::Log("Socket Closed", Utility_General::LogLevel::LevelInfo);

		return Utility_General::ErrorCheck(false);
	}

	Utility_General::ErrorCheck Socket::BindSocket()
	{
		sockaddr_in addressHolder = m_Endpoint.GetSocketAddress();

		//bind() is a WinSock function that returns 0 if no error occurs
		int checkBind = bind(m_Socket, (sockaddr*)&addressHolder, sizeof(sockaddr_in));
		if (checkBind != 0)
		{
			return Utility_General::ErrorCheck(true, "ERROR: ADDRESS BINDING FAILED");
		}
		
		Utility_General::Logger::Log("Address Binded to the Socket Successfully", Utility_General::LogLevel::LevelInfo);

		return Utility_General::ErrorCheck(false);
	}

	Utility_General::ErrorCheck Socket::Listen()
	{
		//listen() is a WinSock function that returns 0 if no error occurs
		int checkListen = listen(m_Socket, m_NumberOfConnections);

		if (checkListen != 0)
		{
			return Utility_General::ErrorCheck(false, "ERROR: UNABLE TO ACCEPT CONNECTIONS");
		}

		Utility_General::Logger::Log("Socket is waiting for connections...", Utility_General::LogLevel::LevelInfo);

		return Utility_General::ErrorCheck(false);
	}

	//
	Utility_General::ErrorCheck Socket::AcceptConnection(Socket& incomingSocket)
	{
		SOCKET connection = accept(m_Socket, nullptr, nullptr);
		if (connection == INVALID_SOCKET)
		{
			return Utility_General::ErrorCheck(true, "ERROR: CONNECTION REFUSED");
		}

		incomingSocket = Socket(connection);
		Utility_General::Logger::Log("CONNECTION ESTABLISHED", Utility_General::LogLevel::LevelInfo);

		return Utility_General::ErrorCheck(false);
	}

	Utility_General::ErrorCheck Socket::RequestConnection()
	{
		sockaddr_in address = m_Endpoint.GetSocketAddress();

		//connect() is a WinSock function that returns 0 if no error occurs
		int checkConnect = connect(m_Socket, (sockaddr*)(&address), sizeof(sockaddr_in));
		if (checkConnect != 0)
		{
			return Utility_General::ErrorCheck(true, "ERROR: CONNECTION ATTEMPT FAILED");
		}

		Utility_General::Logger::Log("Connected ...", Utility_General::LogLevel::LevelInfo);

		return Utility_General::ErrorCheck(false);
	}

	Utility_General::ErrorCheck Socket::SendInt(int value)
	{
		char data[sizeof(int)];

		memcpy(data, &value, sizeof(int));

		// send() is a WinSock function that returns 0 if no error occurs
		int resultCheck = send(m_Socket, data, sizeof(int), NULL);
		if (resultCheck == SOCKET_ERROR)
		{
			return Utility_General::ErrorCheck(true, "ERROR: COULD NOT SEND DATA");
		}

		if (m_Endpoint.GetEndpointState() == Utility_Network::EndpointState::Client)
		{
			m_Endpoint.AddItemToMessageManager(value);
		}

		return Utility_General::ErrorCheck(false);
	}

	Utility_General::ErrorCheck Socket::ReceiveInt(int &value)
	{
		char data[sizeof(int)];

		int bytesReceived = recv(m_Socket, data, sizeof(int), NULL);

		if (bytesReceived == SOCKET_ERROR)
		{
			return Utility_General::ErrorCheck(true, " ERROR: COULDN'T RECEIVE DATA");
		}

		memcpy(&value, &data, sizeof(int));

		if (m_Endpoint.GetEndpointState() == Utility_Network::EndpointState::Client)
		{
			m_Endpoint.SearchForItem(value);
		}
		else
		{
			if (value != 0)
			{
				Utility_General::Logger::Log(std::to_string(value) + " Value Received ", Utility_General::LogLevel::LevelInfo);
			}
			SendInt(value);
		}

		return Utility_General::ErrorCheck(false);
	}


	Utility_General::ErrorCheck Socket::SetupSocket(SocketSettings setting, BOOL value)
	{
		switch (setting)
		{
			case SocketSettings::TCP_NoDelay:
			{
				// setsockopt() is a WinSock function that returns 0 if no error occurs
				int checkSocketSetting = setsockopt(m_Socket, IPPROTO_TCP, TCP_NODELAY, (const char*)&value, sizeof(value));
				if (checkSocketSetting != 0)
				{
					return Utility_General::ErrorCheck(true, "ERROR: SOCKET SETTING FAILED");
				}

				Utility_General::Logger::Log("TCP_NoDelay Set Successfully", Utility_General::LogLevel::LevelInfo);
				return Utility_General::ErrorCheck(false);
			}
			default:
			{
				return Utility_General::ErrorCheck(true, "ERROR: INVALID SOCKET SETTING");
			}
		}
	}

}