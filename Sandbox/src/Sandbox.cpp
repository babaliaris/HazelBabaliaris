#include <Hazel.h>
#include "imgui/imgui.h"
#include "Sandbox2D.h"

namespace Hazel
{
	
};

class MyLayer : public Hazel::Layer
{
public:
	MyLayer()
		: m_CameraController(Hazel::Application::Get().GetWindow().GetWidth() / (float)Hazel::Application::Get().GetWindow().GetHeight(), true)
	{
	}

	~MyLayer(){}


	void OnAttach() override
	{
		float vertices[] =
		{
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f  // top left 
		};

		unsigned int indices[] =
		{
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
		};


		m_vao = Hazel::VertexArray::Create();
		m_vbo = Hazel::VertexBuffer::Create( vertices, sizeof(vertices) );
		m_ebo = Hazel::IndexBuffer::Create( indices, sizeof(indices) / sizeof(unsigned int) );


		Hazel::BufferLayout layout =
		{
			{Hazel::ShaderDataType::FLOAT3, "position"},
			{Hazel::ShaderDataType::FLOAT2, "TexCoords"},
		};

		m_vbo->SetLayout(layout);


		m_vao->AddVertexBuffer(m_vbo);
		m_vao->SetIndexBuffer(m_ebo);
		

		shader_lib.Load("src/Hazel/Renderer/Shaders/Vertex.vert", "src/Hazel/Renderer/Shaders/Fragment.frag");
		m_shader = shader_lib.Get("Vertex.vert_Fragment.frag");

		m_texture = Hazel::Texture2D::Create("Assets/Textures/Checkerboard.png");
		m_cherno  = Hazel::Texture2D::Create("Assets/Textures/ChernoLogo.png");
	}

	void OnUpdate(Hazel::Timestep ts) override 
	{

		m_CameraController.OnUpdate(ts);

		Hazel::Renderer::BeginScene(m_CameraController.GetCamera());


		m_shader->SetUniform("u_Color", glm::vec4(m_square_color, 0.0f));

		float scale = 0.1f;
		float gap	= 0.12f;
		for (int i = 0; i < 10; i++)
		{

			for (int j = 0; j < 10; j++)
			{

				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(j * gap, i * gap, 0.0f));
				model			= glm::scale(model, glm::vec3(scale, scale, scale));
				Hazel::Renderer::Submit(m_vao, m_shader, model);
			}
		}

		m_texture->Bind();
		m_shader->SetUniform("u_Diffuse", 0);
		Hazel::Renderer::Submit(m_vao, m_shader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f, 1.5f, 1.5f)));

		m_cherno->Bind();
		glm::mat4 cherno_model = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, -0.25f, 0.0f));
		cherno_model = glm::scale(cherno_model, glm::vec3(1.5f, 1.5f, 1.5f));
		Hazel::Renderer::Submit(m_vao, m_shader, cherno_model);


		Hazel::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", &m_square_color[0]);
		ImGui::End();
	}

	void OnEvent(Hazel::Event &e) override
	{
		m_CameraController.OnEvent(e);
	}

private:
	Hazel::Ref <Hazel::VertexArray> m_vao;
	Hazel::Ref <Hazel::VertexBuffer> m_vbo;
	Hazel::Ref <Hazel::IndexBuffer> m_ebo;
	Hazel::Ref <Hazel::Shader> m_shader;
	Hazel::Ref <Hazel::Texture> m_texture, m_cherno;

	Hazel::ShaderLibrary shader_lib;

	Hazel::OrthographicCameraController m_CameraController;

	glm::vec3 m_square_color = glm::vec3(0.0f, 0.0f, 0.6f);
};


class MyApp : public Hazel::Application
{
public:

	MyApp()
	{
		//PushLayer(new MyLayer());
		PushLayer(new Sandbox2D());
	}

	~MyApp(){}
};

Hazel::Application *Hazel::createApp()
{
	return new MyApp();
}