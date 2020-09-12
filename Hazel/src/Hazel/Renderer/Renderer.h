#pragma once
#include "RenderComman.h"

namespace Hazel
{
	class Renderer
	{

	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererAPI::API GetApi() { return RendererAPI::GetAPI(); }

	};
}