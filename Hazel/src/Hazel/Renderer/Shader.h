#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H
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

        static Ref<Shader> Create(const char* v_path, const char* f_path);
    };
}

#endif