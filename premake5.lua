workspace "HazelBabaliaris"
	architecture "x64"
	
	configurations 
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	startproject "Sandbox"
	
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	
	IncludeDir = {}
	IncludeDir["GLFW"] 		= "Hazel/vendor/glfw/include"
	IncludeDir["Glad"] 		= "Hazel/vendor/Glad/include"
	IncludeDir["ImGui"] 	= "Hazel/vendor/imgui"
	IncludeDir["GLM"] 		= "Hazel/vendor/glm"
	IncludeDir["STB_IMG"] 	= "Hazel/vendor/stb_image"
	
	group "Depedencies"
		include "Hazel/vendor/glfw"
		include "Hazel/vendor/Glad"
		include "Hazel/vendor/imgui"
	group ""
	
	
	project "Hazel"
		location "Hazel"
		kind "StaticLib"
		language "C++"
		cppdialect "C++17"
		staticruntime "On"
		
		
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
		pchheader "hzpch.h"
		pchsource "Hazel/src/hzpch.cpp"
		
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.c",
			"%{prj.name}/vendor/stb_image/stb_image.h",
			"%{prj.name}/vendor/stb_image/stb_image.cpp",
			"%{prj.name}/vendor/glm/glm/**.hpp",
			"%{prj.name}/vendor/glm/glm/**.inl"
		}
		
		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.STB_IMG}"
		}
		
		
		links
		{
			"GLFW",
			"Glad",
			"ImGui",
			"opengl32.lib"
		}
		
		
		defines{
			"_CRT_SECURE_NO_WARNINGS"
		}
		
		
		
		filter "system:windows"
			staticruntime "On"
			systemversion "latest"
			
			defines
			{
				"HZ_PLATFORM_WINDOWS",
				"HZ_STATIC_LINK",
				"HZ_ENABLE_ASSERTS",
				"GLFW_INCLUDE_NONE"
			}
			
		filter "configurations:Debug"
			defines "HZ_DEBUG"
			runtime "Debug"
			symbols "On"
			
		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			optimize "On"
			
		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			optimize "On"
	
	
	
	
	
	
	
	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++17"
		staticruntime "On"
		
		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
		
		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/src/**.c"
		}
		
		includedirs
		{
			"Hazel/vendor/spdlog/include",
			"Hazel/src",
			"Hazel/vendor",
			"%{IncludeDir.GLM}",
			"%{IncludeDir.Glad}"
		}
		
		links "Hazel"
		
		filter "system:windows"
			systemversion "latest"
			
			defines
			{
				"HZ_PLATFORM_WINDOWS",
				"HZ_STATIC_LINK",
				"HZ_ENABLE_ASSERTS"
			}
			
		filter "configurations:Debug"
			defines "HZ_DEBUG"
			runtime "Debug"
			symbols "On"
			
		filter "configurations:Release"
			defines "HZ_RELEASE"
			runtime "Release"
			optimize "On"
			
		filter "configurations:Dist"
			defines "HZ_DIST"
			runtime "Release"
			optimize "On"
				