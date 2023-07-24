#pragma once

#include<GLFW/glfw3.h>
#include<glad/glad.h>
#include<iostream>

namespace MY_WINDOW
{
    class GLFWWindow
    {
    private:
        GLFWwindow* window;
    public:
        GLFWWindow(int width, int height, const char* title)
        {

            glfwInit();
            // 设置OpenGL版本为3.3
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            // 设置OpenGL配置为核心模式
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            // 创建窗口
            window = glfwCreateWindow(width, height, title, NULL, NULL);
            // 判断窗口是否创建成功
            if (window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                // 创建失败则终止程序
                glfwTerminate();
                return;
            }

            glfwMakeContextCurrent(window);

            if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                glfwTerminate();
                return;
            }

            glViewport(0, 0, width, height);

        }
        GLFWwindow* getWindow()
        {
            return window;
        }
        void setWindow(GLFWwindow* window)
        {
            this->window = window;
        }
    };
}