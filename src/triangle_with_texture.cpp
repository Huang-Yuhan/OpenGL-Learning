#include<glad/glad.h>
#include "../include/GLFWWindow.hpp"
#include "../include/Image.hpp"
#include "../include/Shader.hpp"
#include "../include/BufferObject.hpp"

int main()
{
    MY_WINDOW::GLFWWindow glfwWindow(800, 600, "Triangle with texture");
    auto window = glfwWindow.getWindow();

    float vertices[] = {
    //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
    };

    unsigned int indices[] = {
        // 注意索引从0开始! 
        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
        // 这样可以由下标代表顶点组合成矩形

        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    BUFFER_OBJECT::VBO vbo;
    vbo.bind();
    vbo.setBufferData(sizeof(vertices), vertices, GL_STATIC_DRAW);

    BUFFER_OBJECT::VAO vao;
    vao.bind();
    
    BUFFER_OBJECT::VAO_LAYOUT vaoLayout;
    vaoLayout.push(3);
    vaoLayout.push(3);
    vaoLayout.push(2);

    vao.setVertexAttribPointer(vaoLayout);

    BUFFER_OBJECT::EBO ebo;
    ebo.bind();
    ebo.setBufferData(sizeof(indices), indices, GL_STATIC_DRAW);

    MY_SHADER::Shader shader;

    shader.setVertexShaderByPath("../src/shader/triangle_texture.vert");
    shader.setFragmentShaderByPath("../src/shader/triangle_texture.frag");
    shader.linkShaderProgram();

    MY_IMAGE::Texture texture("../assets/texture/container.jpg");

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 设置清空屏幕所用的颜色
        glClear(GL_COLOR_BUFFER_BIT); // 清空屏幕的颜色缓冲

        shader.use();
        vao.bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    return 0;
}