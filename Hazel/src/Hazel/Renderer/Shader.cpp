#include <hzpch.h>
#include "Shader.h"
#include "Hazel/Core.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"



namespace Hazel
{
	Ref<Shader> Shader::Create(const char* v_path, const char* f_path)
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
				return Ref<Shader>(new OpenGLShader(v_path, f_path));
			}
		}

		HZ_CORE_ASSERT(false, "Uknown renderer api.");
		return nullptr;
	}





	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		HZ_CORE_ASSERT( m_shaders.find(shader->GetName()) == m_shaders.end(), "Shader already exists!");
		m_shaders[shader->GetName()] = shader;
	}



	Ref<Shader> ShaderLibrary::Load(const std::string& vert_path, const std::string& frag_path)
	{
		Ref<Shader> shader = Shader::Create(vert_path.c_str(), frag_path.c_str());
		this->Add(shader);
		return shader;
	}


	/**
	* Shader name signature: VertexName.vert_FragmentName.frag
	*/
	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		HZ_CORE_ASSERT(m_shaders.find(name) != m_shaders.end(), "Shader did not found!");
		return m_shaders[name];
	}
}