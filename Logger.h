//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once
#include <iostream>
#include <chrono>

namespace Utility_General
{
	enum class LogLevel
	{
		LevelError = 0,
		LevelWarning,
		LevelInfo
	};

	class Logger
	{
	public:
		static void Log(std::string info, LogLevel level);

	private:
		static void _LogError(std::string info);
		static void _LogWarning(std::string info);
		static void _LogInfo(std::string info);
	};
}