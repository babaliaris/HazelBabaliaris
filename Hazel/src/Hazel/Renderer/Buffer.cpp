#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hazel
{
	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, unsigned int size)
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
				return Ref<VertexBuffer>(std::make_shared<OpenGLVertexBuffer>(vertices, size));
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}



	Ref<IndexBuffer> IndexBuffer::Create(unsigned int* indices, unsigned int count)
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
				return Ref<IndexBuffer>(std::make_shared <OpenGLIndexBuffer>(indices, count));
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}
}