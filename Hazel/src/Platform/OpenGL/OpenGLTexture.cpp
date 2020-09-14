#include "hzpch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
#include <stb_image.h>

namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path)
	{
		stbi_set_flip_vertically_on_load(1);

		std::string full_path = std::string(SANDBOX_DIR) + path;

		int width, height, channels;
		unsigned char* data = stbi_load(full_path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "Failed to load image.");

		m_Width		= width;
		m_Height	= height;

		unsigned int internal_format, format;
		if (channels == 4)
		{
			internal_format = GL_RGBA8;
			format = GL_RGBA;
		}
		else
		{
			internal_format = GL_RGB8;
			format = GL_RGB;
		}

		HZ_CORE_ASSERT(internal_format & format, "Format not supported.");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internal_format, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, format, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

	}


	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}


	void OpenGLTexture2D::Bind(unsigned int slot)
	{
		glBindTextureUnit(slot, m_RendererID);
	}


	void OpenGLTexture2D::Unbind()
	{
	}
}
