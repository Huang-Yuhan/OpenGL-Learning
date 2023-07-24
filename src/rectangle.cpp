#include<glad/glad.h>
#include "../include/BufferObject.hpp"
#include "../include/Shader.hpp"
#include "../include/GLFWWindow.hpp"

int main()
{


    MY_WINDOW::GLFWWindow glfwWindow(800, 600, "LearnOpenGL");
    GLFWwindow* window = glfwWindow.getWindow();

    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };

    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    // 创建顶点缓冲对象
    BUFFER_OBJECT::VBO vbo;
    // 绑定顶点缓冲对象
    vbo.bind();
    // 将顶点数据复制到顶点缓冲对象中
    vbo.setBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 创建顶点数组对象
    BUFFER_OBJECT::VAO vao;
    // 绑定顶点数组对象
    vao.bind();
    // 设置顶点属性指针
    vao.setVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);

    // 创建索引缓冲对象
    BUFFER_OBJECT::EBO ebo;
    // 绑定索引缓冲对象
    ebo.bind();
    // 将索引数据复制到索引缓冲对象中
    ebo.setBufferData(sizeof(indices), indices, GL_STATIC_DRAW);

    // 创建着色器程序
    MY_SHADER::Shader shader;
    // 设置顶点着色器源码
    shader.setVertexShaderByPath("../src/shader/triangle.vert");
    // 设置片段着色器源码
    shader.setFragmentShaderByPath("../src/shader/triangle.frag");
    // 链接着色器程序
    shader.linkShaderProgram();

    // 渲染循环
    while(!glfwWindowShouldClose(window))
    {

        // 渲染指令
        // ...
        // 清除颜色缓冲
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 状态设置函数
        glClear(GL_COLOR_BUFFER_BIT);         // 状态使用函数

        // 绘制三角形
        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 交换缓冲并查询IO事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}