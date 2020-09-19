#pragma once
#include <chrono>

namespace Hazel
{
	class Timer
	{

	public:

		Timer(const char* name);
		~Timer();

		void Stop();


	private:
		const char* m_Name;
		bool m_Stoped;

		std::chrono::steady_clock::time_point m_Start;

	};
}

