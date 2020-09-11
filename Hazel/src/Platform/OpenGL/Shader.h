#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H
#include <iostream>
#include <glm/glm.hpp>

namespace Hazel
{
    class Shader
    {
        public:

        Shader(const char *v_path, const char *f_path);

        void Use();

        void SetUniform(const char *name, int x);
        void SetUniform(const char *name, float x);
        void SetUniform(const char *name, glm::vec3 &vec3);
        void SetUniform(const char *name, glm::mat4 &mat4);

        private:
        unsigned int m_id;
        std::string m_vertex_path, m_fragment_path;

        std::string ReadFile(std::string &path);

        unsigned int CompileShader(int type, std::string &path);

        int GetLocation(const char *name);
    };
}

#endif