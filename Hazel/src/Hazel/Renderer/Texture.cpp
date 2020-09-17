#include "hzpch.h"
#include "Texture.h"
#include "Hazel/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetApi())
		{
			case RendererAPI::API::None:
			{
				HZ_CORE_ASSERT(false, "RendererAPI::None is not currently supported.");
				return nullptr;
			}

			case RendererAPI::API::OpenGL:
			{
				return Ref<Texture2D>(std::make_shared<OpenGLTexture2D>(path));
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}



	Ref<Texture2D> Texture2D::Create(unsigned int width, unsigned int height)
	{
		switch (Renderer::GetApi())
		{
		case RendererAPI::API::None:
		{
			HZ_CORE_ASSERT(false, "RendererAPI::None is not currently supported.");
			return nullptr;
		}

		case RendererAPI::API::OpenGL:
		{
			return Ref<Texture2D>(std::make_shared<OpenGLTexture2D>(width, height));
		}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}
}