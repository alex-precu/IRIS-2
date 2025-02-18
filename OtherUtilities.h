//Code Owner: Alexandru Precupetu
//Restricted: No

#pragma once

#include <string>

namespace Utility_General
{
	class ErrorCheck
	{
	public:
		ErrorCheck(bool isFailed, std::string ErrorCheckText = "")
		{
			m_IsFailed = isFailed;
			m_ErrorCheckText = ErrorCheckText;
		}

		bool IsFailed() { return m_IsFailed; }
		std::string GetErrorCheckDescription() const { return m_ErrorCheckText; }

	private:
		std::string m_ErrorCheckText;
		bool m_IsFailed;
	};
}
