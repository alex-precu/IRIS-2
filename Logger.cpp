//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once

#include "Logger.h"

namespace Utility_General
{
	void Logger::Log(std::string info, LogLevel level)
	{
		switch(level)
		{
			case LogLevel::LevelError:
			{
				_LogError(info);
				break;
			}
			case LogLevel::LevelWarning:
			{
				_LogWarning(info);
				break;
			}
			case LogLevel::LevelInfo:
			{
				_LogInfo(info);
				break;
			}
			default:
			{
				std::cout << "LOGGING ERROR\n";
				break;
			}
		}
	}

	void Logger::_LogError(std::string info)
	{
		std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char timeBuffer[30];
		ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime);
		std::cout << timeBuffer << "ERROR>>> " << info << std::endl;
		std::cout << "X-X-X-X-X-X-X-X-X-X" << std::endl;
	}

	void Logger::_LogWarning(std::string info)
	{
		std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char timeBuffer[30];
		ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime);
		std::cout << timeBuffer << "WARNING>> " << info << std::endl;
		std::cout << "W-W-W-W-W-W-W-W-W-W" << std::endl;
	}

	void Logger::_LogInfo(std::string info)
	{

		std::time_t currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char timeBuffer[30];
		ctime_s(timeBuffer, sizeof(timeBuffer), &currentTime);
		std::cout << timeBuffer << "STATUS UPDATE> " << info << std::endl;
		std::cout << "--------------------" << std::endl;
	}
}