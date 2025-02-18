//Code Owner: Alexandru Precupetu
//Restricted: No

#include <iostream>
#include <thread>

#include "OtherUtilities.h"
#include "WinSock2Loader.h"
#include "Socket.h"



void InitializeServer(Utility_Network::Socket& socket)
{
	Utility_General::ErrorCheck err = socket.InitSocket("127.0.0.1", 9999, Utility_Network::EndpointState::Server);
	if (!err.IsFailed())
	{
		err = socket.BindSocket();
		if (!err.IsFailed())
		{
			err = socket.Listen();
			if (!err.IsFailed())
			{
				err = socket.AcceptConnection(socket);
				if (err.IsFailed())
				{
					Utility_General::Logger::Log(err.GetErrorCheckDescription(), Utility_General::LogLevel::LevelError);
				}
			}
			else
			{
				Utility_General::Logger::Log(err.GetErrorCheckDescription(), Utility_General::LogLevel::LevelError);
			}
		}
		else
		{
			Utility_General::Logger::Log(err.GetErrorCheckDescription(), Utility_General::LogLevel::LevelError);
		}
		
	}
	else
	{
		Utility_General::Logger::Log(err.GetErrorCheckDescription(), Utility_General::LogLevel::LevelError);
	}
}

void InitializeClient(Utility_Network::Socket& socket)
{
	Utility_General::ErrorCheck err = socket.InitSocket("127.0.0.1", 9999, Utility_Network::EndpointState::Client);
	if (!err.IsFailed())
	{
		err = socket.RequestConnection();
		if (err.IsFailed())
		{
			Utility_General::Logger::Log(err.GetErrorCheckDescription(), Utility_General::LogLevel::LevelError);
		}
	}
}

void ReceiveLoop(Utility_Network::Socket& socket)
{
	int t = 0;
	while (true)
	{
		socket.ReceiveInt(t);
	}
}

void GiveIntsEvery2Seconds(Utility_Network::Socket& socket)
{
	for (int i = 0; i < 100; ++i)
	{
		socket.SendInt(i);
		Sleep(2000);
	}
}

void GiveIntsEverySecond(Utility_Network::Socket& socket)
{
	for (int i = 100; i > 0; i--)
	{
		socket.SendInt(i);
		Sleep(1000);
	}
}


int main()
{

	Utility_General::ErrorCheck err(false);

	int choice = 0;
	int receivedInt = 0;
	Utility_Network::Socket socket;

	if (Utility_Network::WinSockLoader::EnableWinSock())
	{
		
		std::cout << "Chose type of endpoint \n 1. Client\n 2. Server\n";

		std::cin >> choice;

		if (choice == 2)
		{

			InitializeServer(socket);
			while (true)
			{
				socket.ReceiveInt(receivedInt);
				if (rand() % 2 == 0)
				{
					Sleep(1111);
				}
			}

		}

		else
		{
			InitializeClient(socket);
			int state = 0;

			std::thread ReceiveThread(ReceiveLoop, std::ref(socket));

			std::thread intFactory1(GiveIntsEvery2Seconds, std::ref(socket));
			std::thread intFactory2(GiveIntsEverySecond, std::ref(socket));

			while (state != -1)
			{
				std::cin >> state;
				
				socket.SendInt(state);

			}
		}

	}

	return 0;
}