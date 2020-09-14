#pragma once
#include "RenderCommand.h"
#include "OrthographicCamera.h"
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
	class Renderer
	{

	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1));

		inline static RendererAPI::API GetApi() { return RendererAPI::GetAPI(); }

		static void Init();

	private:
		
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData *s_SceneData;

	};
}