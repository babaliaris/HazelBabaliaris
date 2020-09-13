#include <Hazel.h>
#include "imgui/imgui.h"

namespace Hazel
{
	
};

class MyLayer : public Hazel::Layer
{
public:
	MyLayer()
		: m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{
	}

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

	void OnUpdate(Hazel::Timestep ts) override 
	{

		float x = 0, y = 0;
		glm::vec3 direction = { 0.0f, 0.0f, 0.0f };

		if (Hazel::Input::IsKeyPressed(HZ_KEY_W))
			y = 1;

		else if (Hazel::Input::IsKeyPressed(HZ_KEY_S))
			y = -1;

		if (Hazel::Input::IsKeyPressed(HZ_KEY_A))
			x = -1;

		else if (Hazel::Input::IsKeyPressed(HZ_KEY_D))
			x = 1;

		if (x != 0 || y != 0)
			direction = glm::normalize(glm::vec3(x, y, 0.0f));

		m_Camera.SetPosition(m_Camera.GetPosition() + ts * direction);

		Hazel::Renderer::BeginScene(m_Camera);

		Hazel::Renderer::Submit(m_vao, m_shader);

		Hazel::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(Hazel::Event &e)
	{
		Hazel::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Hazel::KeyPressedEvent>(HZ_BIND_EVENT_FN(MyLayer::OnKeyPress));
	}

	bool OnKeyPress(Hazel::KeyPressedEvent& event)
	{
		return false;
	}

private:
	std::shared_ptr < Hazel::VertexArray> m_vao;
	std::shared_ptr < Hazel::VertexBuffer> m_vbo;
	std::shared_ptr < Hazel::IndexBuffer> m_ebo;
	std::shared_ptr < Hazel::Shader> m_shader;

	Hazel::OrthographicCamera m_Camera;
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