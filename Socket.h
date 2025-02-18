//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once
#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>

#include "OtherUtilities.h"
#include "Endpoint.h"


namespace Utility_Network
{
	enum class SocketSettings
	{
		TCP_NoDelay, //disables package size optimizations
	};

	class Socket
	{
	public:
		Socket(SOCKET m_Socket = INVALID_SOCKET);

		//Wrapper over Winsock's scoket() function, sets basic socket options
		Utility_General::ErrorCheck InitSocket(const char* ip, unsigned int port, Utility_Network::EndpointState state);

		//Wrapper over Winsock's closesocket() function, invalidates m_Socket
		Utility_General::ErrorCheck CloseSocket();

		//Wrapper over Winsock's bind() function, binds the socket to the specified port
		Utility_General::ErrorCheck BindSocket();

		//Wrapper over Winsock's listen() function, sets the socket state to listen for connections 
		Utility_General::ErrorCheck Listen();

		///Wrapper over Winsock's accept() function,checks if the connection is valid and creates
		//the socket responsable for the connection
		Utility_General::ErrorCheck AcceptConnection(Socket& incomingSocket);

		//Wrapper over Winsock's connect() function, attempts to connect to another socket.
		Utility_General::ErrorCheck RequestConnection();

		//Function used to send int type data over the connection, manages data packing
		Utility_General::ErrorCheck SendInt(int value);

		//Function used to receive int type data over the connection, manages data unpacking
		Utility_General::ErrorCheck ReceiveInt(int &value);

		//Helper function that sets the value of socket settings found in enum class SocketSettings
		Utility_General::ErrorCheck SetupSocket(SocketSettings setting, BOOL value);

	private:

		SOCKET m_Socket = INVALID_SOCKET;
		bool m_IsConnected;
		Endpoint m_Endpoint;
		unsigned int m_NumberOfConnections;
		
	};
}


