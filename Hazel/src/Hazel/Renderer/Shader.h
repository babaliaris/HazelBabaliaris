#pragma once
#include <iostream>
#include <glm/glm.hpp>

namespace Hazel
{
    class Shader
    {
        public:

        virtual ~Shader()     = default;
        virtual void Bind()   = 0;
        virtual void Unbind() = 0;

        virtual const std::string& GetName() const = 0;

        virtual void SetUniform(const std::string& name, int x) = 0;
        virtual void SetUniform(const std::string& name, float x) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec3& vec3) = 0;
        virtual void SetUniform(const std::string& name, const glm::vec4& vec4) = 0;
        virtual void SetUniform(const std::string& name, const glm::mat4& mat4) = 0;

        static Ref<Shader> Create(const char* v_path, const char* f_path);
    };


    class ShaderLibrary
    {

    public:

        void Add(const Ref<Shader>& shader);
        Ref<Shader> Load(const std::string& vert_path, const std::string& frag_path);
        Ref<Shader> Get(const std::string& name);



    private:

        std::unordered_map<std::string, Ref<Shader>> m_shaders;

    };
}