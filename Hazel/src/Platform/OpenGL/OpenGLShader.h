#pragma once
#include <iostream>
#include "Hazel/Renderer/Shader.h"

namespace Hazel
{
    class OpenGLShader : public Shader
    {
        public:

        OpenGLShader(const char *v_path, const char *f_path);
        virtual ~OpenGLShader();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual const std::string& GetName() const override;

        void SetUniform(const char *name, int x);
        void SetUniform(const char *name, float x);
        void SetUniform(const char *name, const glm::vec3 &vec3);
        void SetUniform(const char* name, const glm::vec4& vec4);
        void SetUniform(const char *name, const glm::mat4 &mat4);

        private:
        unsigned int m_id;
        std::string m_vertex_path, m_fragment_path, m_name;

        std::string ReadFile(std::string &path);

        unsigned int CompileShader(int type, std::string &path);

        int GetLocation(const char *name);
    };
}