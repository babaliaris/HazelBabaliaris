#include <hzpch.h>
#include "OpenGLShader.h"
#include <glad/glad.h>
#include "Hazel/Core/Core.h"
#include <fstream>
#include <sstream>



namespace Hazel
{
    OpenGLShader::OpenGLShader(const char *v_path, const char *f_path)
        : m_id(0), m_vertex_path(v_path), m_fragment_path(f_path)
    {

        //--------------------Create the name of this shader--------------------//
        auto lastShashVert = m_vertex_path.find_last_of("/");
        lastShashVert = lastShashVert == std::string::npos ? 0 : lastShashVert + 1;

        auto lastShashFrag = m_fragment_path.find_last_of("/");
        lastShashFrag = lastShashFrag == std::string::npos ? 0 : lastShashFrag + 1;

        //Create the name of this shader.
        m_name = m_vertex_path.substr(lastShashVert, m_vertex_path.length()) + "_" +
            m_fragment_path.substr(lastShashFrag, m_fragment_path.length());
        //--------------------Create the name of this shader--------------------//

        //Compile the vertex and the fragment shaders.
        unsigned int vertex     = this->CompileShader(GL_VERTEX_SHADER, m_vertex_path);
        unsigned int fragment   = this->CompileShader(GL_FRAGMENT_SHADER, m_fragment_path);

        //If the vertex and the fragment shaders where compiled successfully.
        if (vertex && fragment)
        {
            m_id = glCreateProgram();

            glAttachShader(m_id, vertex);
            glAttachShader(m_id, fragment);

            glLinkProgram(m_id);
            glValidateProgram(m_id);

            //----------Check For Linking Errors----------//
            int success;
            int length;

            //Get the status;
            glGetProgramiv(m_id, GL_LINK_STATUS, &success);

            //Something went wrong.
            if (!success)
            {

                //Get the info log length.
                glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &length);

                //Create a unique ptr to strore the message.
                std::unique_ptr<char> message = std::make_unique<char>(length);

                //Get the info log.
                glGetProgramInfoLog(m_id, length, NULL, message.get());

                //Assert it.
                HZ_CORE_ASSERT(0, "[ {0} && {1} ] => {2}", v_path, f_path, message.get());
            }
            //----------Check For Linking Errors----------//

        }
    }




    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_id);
    }


    void OpenGLShader::Bind()
    {
        glUseProgram(m_id);
    }

    void OpenGLShader::Unbind()
    {
        glUseProgram(0);
    }

    const std::string& OpenGLShader::GetName() const
    {
        return m_name;
    }


    void OpenGLShader::SetUniform(const char *name, int x)
    {
        glUniform1i(this->GetLocation(name), x);
    }


    void OpenGLShader::SetUniform(const char *name, float x)
    {
        glUniform1f(this->GetLocation(name), x);
    }


    void OpenGLShader::SetUniform(const char *name, const glm::vec3 &vec3)
    {
        glUniform3f(this->GetLocation(name), vec3.x, vec3.y, vec3.z);
    }


    void OpenGLShader::SetUniform(const char* name, const glm::vec4& vec4)
    {
        glUniform4f(this->GetLocation(name), vec4.x, vec4.y, vec4.z, vec4.w);
    }

    void OpenGLShader::SetUniform(const char *name, const glm::mat4 &mat4)
    {
        glUniformMatrix4fv(this->GetLocation(name), 1, GL_FALSE, (const GLfloat *)&mat4[0]);
    }






    std::string OpenGLShader::ReadFile(std::string &path)
    {
        std::string full_path = std::string(RUNTIME_DIR) + path;
        std::ifstream file(full_path.c_str());

        //If the file opened successfully.
        if (file.is_open())
        {
            std::stringstream ss;

            ss << file.rdbuf();

            file.close();

            return ss.str();
        }

        HZ_CORE_ASSERT(0, "The file: {0} could not be opened.", full_path);
        return "";
    }


    unsigned int OpenGLShader::CompileShader(int type, std::string &path)
    {

        //Create the src string.
        std::string source  = this->ReadFile(path);
        const char *src     = source.c_str();
        
        //Create and compile the shader.
        unsigned int shader = glCreateShader(type);
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        //----------Check For Compilation Errors----------//
        int success;
        int length;

        //Get the status;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        //Something went wrong.
        if (!success)
        {

            //Get the info log length.
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

            //Create a unique ptr to strore the message.
            std::unique_ptr<char> message = std::make_unique<char>(length);

            //Get the info log.
            glGetShaderInfoLog(shader, length, NULL, message.get());

            //Assert it.
            HZ_CORE_ASSERT(0, "[ {0} ] => {1}", path, message.get());

            return -1;
        }
        //----------Check For Compilation Errors----------//

        return shader;
    }



    int OpenGLShader::GetLocation(const char *name)
    {

        //Bind the program;
        this->Bind();

        //Get the uniform location.
        int location = glGetUniformLocation(m_id, name);

        //Assert the location.
        HZ_CORE_ASSERT(location != -1, "[ {0} && {1} ] => Uniform [ {2} ] does not exist!", m_vertex_path, m_fragment_path, name);

        return location;
    }
}