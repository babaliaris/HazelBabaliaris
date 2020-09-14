#pragma once
#include <memory>

#ifdef HZ_PLATFORM_WINDOWS
	
	//DLL.
	#ifndef HZ_STATIC_LINK

		#ifdef HZ_BUILD_DLL
			#define HAZEL_API _declspec(dllexport)
		#else
			#define HAZEL_API _declspec(dllimport)
		#endif
	
	//Static Linking.
	#else
		#define HAZEL_API

	#endif


	//Runtime Directory.
	#define RUNTIME_DIR "../Hazel/"
	#define SANDBOX_DIR ""

#else
	#error Hazel only supports windows!

#endif

#define BIT(x) (1 << x)


#ifdef HZ_ENABLE_ASSERTS

	#define HZ_ASSERT(x, ...) { if (!(x)) {HZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) { if (!(x)) {HZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }

#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)

#endif


#define HZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace Hazel
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}