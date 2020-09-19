#include "hzpch.h"
#include "Timer.h"

Hazel::Timer::Timer(const char* name)
	: m_Name(name), m_Stoped(false)
{

	//Get the starting time.
	m_Start = std::chrono::high_resolution_clock::now();
}



Hazel::Timer::~Timer()
{
	if (!m_Stoped)
		this->Stop();
}



void Hazel::Timer::Stop()
{

	//Get the end time.
	std::chrono::steady_clock::time_point m_End = std::chrono::high_resolution_clock::now();

	long long s_us = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_Start).time_since_epoch().count();
	long long e_us = std::chrono::time_point_cast<std::chrono::nanoseconds>(m_End).time_since_epoch().count();

	//Micro Seconds.
	double us = (e_us - s_us) * 0.001f;

	//Milli Seconds.
	double ms = us * 0.001f;

	//Seconds.
	double s  = ms * 0.001f;

	std::cout << us << "us , " << ms << "ms , " << s << "s" << std::endl;

	//Stop The Timer.
	m_Stoped = true;
}
