#include <Hazel.h>
#include "imgui/imgui.h"

#include "Hazel/Renderer/Buffer.h"
#include "Platform/OpenGL/Shader.h"
#include "Hazel/Renderer/VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel
{
	
};

class MyLayer : public Hazel::Layer
{
public:
	MyLayer(){}

	~MyLayer(){}


	void OnAttach() override
	{
		float vertices[] =
		{
			 0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f, //Upper.
			-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f, //Bottom Left.
			 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 1.0f, 1.0f  //Bottom Right.
		};

		unsigned int indices[] =
		{
			0, 1, 2
		};


		m_vao.reset( Hazel::VertexArray::Create() );
		m_vbo.reset( Hazel::VertexBuffer::Create( vertices, sizeof(vertices) ) );
		m_ebo.reset( Hazel::IndexBuffer::Create( indices, sizeof(indices) / sizeof(unsigned int) ) );


		Hazel::BufferLayout layout =
		{
			{Hazel::ShaderDataType::FLOAT3, "position"},
			{Hazel::ShaderDataType::FLOAT4, "color"}
		};

		m_vbo->SetLayout(layout);


		m_vao->AddVertexBuffer(m_vbo);
		m_vao->SetIndexBuffer(m_ebo);
		

		m_shader.reset( new Hazel::Shader("src/Hazel/Renderer/Shaders/Vertex.vert", "src/Hazel/Renderer/Shaders/Fragment.frag") );
	}

	void OnUpdate() override 
	{

		Hazel::Renderer::BeginScene();

		//m_vao->Bind();
		m_shader->Use();
		Hazel::Renderer::Submit(m_vao);

		Hazel::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Hazel::Event &e)
	{
	}

private:
	std::shared_ptr < Hazel::VertexArray> m_vao;
	std::shared_ptr < Hazel::VertexBuffer> m_vbo;
	std::shared_ptr < Hazel::IndexBuffer> m_ebo;
	std::shared_ptr < Hazel::Shader> m_shader;
};


class MyApp : public Hazel::Application
{
public:

	MyApp()
	{
		PushLayer(new MyLayer());
	}

	~MyApp(){}
};

Hazel::Application *Hazel::createApp()
{
	return new MyApp();
}