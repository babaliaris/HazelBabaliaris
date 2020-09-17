#pragma once
#include "Hazel/Renderer/Texture.h"
#include <glad/glad.h>

namespace Hazel
{
	class OpenGLTexture2D : public Texture2D
	{

	public:
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(unsigned int width, unsigned int height);
		virtual ~OpenGLTexture2D();

		inline virtual unsigned int GetWidth() const override { return m_Width; }
		inline virtual unsigned int GetHeight() const override { return m_Height; }

		virtual void SetData(void* data, unsigned int size) override;

		virtual void Bind(unsigned int slot = 0) override;
		virtual void Unbind() override;

	private:
		std::string m_Path;
		unsigned int m_Width	  = 0;
		unsigned int m_Height	  = 0;
		unsigned int m_RendererID = 0;
		GLenum m_InternalFormat, m_Format;

	};
}

