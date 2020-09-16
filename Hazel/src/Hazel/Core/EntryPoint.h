#pragma once

#ifdef HZ_PLATFORM_WINDOWS

namespace Hazel
{
	extern Application* createApp();
}

int main()
{
	Hazel::Log::init();

	Hazel::Application* app = Hazel::createApp();
	app->run();
	delete app;

	return 0;
}

#else
#error Hazel only supports windows!

#endif