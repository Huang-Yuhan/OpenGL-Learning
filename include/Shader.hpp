#pragma once

#include<glad/glad.h>
#include<iostream>
#include<fstream>
#include<string>

namespace MY_SHADER
{
    typedef unsigned int SHADER_PROGRAM_ID_TPYE;
    typedef unsigned int SHADER_ID_TYPE;
    constexpr SHADER_PROGRAM_ID_TPYE INVALID_SHADER_PROGRAM_ID = 0;
    constexpr SHADER_ID_TYPE INVALID_SHADER_ID = 0;

    class Shader
    {
    private:
        SHADER_PROGRAM_ID_TPYE shaderProgramID;
        SHADER_ID_TYPE vertexShaderID;
        SHADER_ID_TYPE fragmentShaderID;
    public:
        Shader()
        {
            shaderProgramID = INVALID_SHADER_PROGRAM_ID;
            vertexShaderID = INVALID_SHADER_ID;
            fragmentShaderID = INVALID_SHADER_ID;
        }
        /**
         * @brief Set the Vertex Shader object
         * 
         * @param vertexShaderSource 给定的顶点着色器源码
         */
        void setVertexShaderByStr(const char* vertexShaderSource)
        {
            if(vertexShaderID != INVALID_SHADER_ID)
            {
                glDeleteShader(vertexShaderID);
            }
            vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertexShaderID, 1, &vertexShaderSource, NULL);
            compileVertexShader();
        }
        /**
         * @brief 
         * 编译给定的Vertex Shader源码
         * 如果编译失败，输出错误信息
         */
        void compileVertexShader()
        {
            glCompileShader(vertexShaderID);
            int success;
            char infoLog[512];
            glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }
        /**
         * @brief 
         * 编译给定的Fragment Shader源码
         * 如果编译失败，输出错误信息
         */
        void complieFragmentShader()
        {
            glCompileShader(fragmentShaderID);
            int success;
            char infoLog[512];
            glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
            if(!success)
            {
                glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
            }
        }

        /**
         * @brief Set the Vertex Shader By Path object
         * 
         * @param vertexShaderPath 
         */
        void setVertexShaderByPath(const char* vertexShaderPath)
        {
            std::ifstream fin(vertexShaderPath);
            if(fin.fail())
            {
                std::cout << "ERROR::SHADER::FILE::OPEN_FAILED\n" << std::endl;
                return;
            }
            std::string vertexShaderSource((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
            setVertexShaderByStr(vertexShaderSource.c_str());
            fin.close();
        }

        /**
         * @brief Set the Fragment Shader object
         * 
         * @param fragmentShaderSource 
         */
        void setFragmentShaderByStr(const char* fragmentShaderSource)
        {
            if(fragmentShaderID != INVALID_SHADER_ID)
            {
                glDeleteShader(fragmentShaderID);
            }
            fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragmentShaderID, 1, &fragmentShaderSource, NULL);
            complieFragmentShader();
        }

        /**
         * @brief Set the Fragment Shader By Path object
         * 
         * @param fragmentShaderPath 
         */
        void setFragmentShaderByPath(const char* fragmentShaderPath)
        {
            std::ifstream fin(fragmentShaderPath);
            if(fin.fail())
            {
                std::cout << "ERROR::SHADER::FILE::OPEN_FAILED\n" << std::endl;
                return;
            }
            std::string fragmentShaderSource((std::istreambuf_iterator<char>(fin)), std::istreambuf_iterator<char>());
            setFragmentShaderByStr(fragmentShaderSource.c_str());
            fin.close();
        }

        /**
         * @brief 
         * 链接顶点着色器和片段着色器到着色器程序
         */
        void linkShaderProgram()
        {
            if(shaderProgramID != INVALID_SHADER_PROGRAM_ID)
            {
                glDeleteProgram(shaderProgramID);
            }
            shaderProgramID = glCreateProgram();
            glAttachShader(shaderProgramID, vertexShaderID);
            glAttachShader(shaderProgramID, fragmentShaderID);
            glLinkProgram(shaderProgramID);
            int success;
            char infoLog[512];
            glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
            if(!success)
            {
                glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
                std::cout << "ERROR::SHADER::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
            }
        }
        /**
         * @brief 
         * 启用该着色器程序
         */
        void use()
        {
            glUseProgram(shaderProgramID);
        }

        void setBool(const std::string &name, bool value) const
        {         
            glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value); 
        }

        void setInt(const std::string &name, int value) const
        { 
            glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
        }

        void setFloat(const std::string &name, float value) const
        { 
            glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value); 
        }

        void setVec2(const std::string &name, float x, float y) const
        { 
            glUniform2f(glGetUniformLocation(shaderProgramID, name.c_str()), x, y); 
        }

    };
}