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

        virtual void SetUniform(const std::string& name, int x) override;
        virtual void SetUniform(const std::string& name, float x) override;
        virtual void SetUniform(const std::string& name, const glm::vec3& vec3) override;
        virtual void SetUniform(const std::string& name, const glm::vec4& vec4) override;
        virtual void SetUniform(const std::string& name, const glm::mat4& mat4) override;

        void UploadUniform(const char *name, int x);
        void UploadUniform(const char *name, float x);
        void UploadUniform(const char *name, const glm::vec3 &vec3);
        void UploadUniform(const char* name, const glm::vec4& vec4);
        void UploadUniform(const char *name, const glm::mat4 &mat4);

        private:
        unsigned int m_id;
        std::string m_vertex_path, m_fragment_path, m_name;

        std::string ReadFile(std::string &path);

        unsigned int CompileShader(int type, std::string &path);

        int GetLocation(const char *name);
    };
}