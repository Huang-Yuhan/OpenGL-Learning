#include<glad/glad.h>
#include "../include/GLFWWindow.hpp"
#include "../include/Camera.hpp"
#include "../include/BufferObject.hpp"
#include "../include/Image.hpp"
#include "../include/Shader.hpp"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

MY_WINDOW::GLFWWindow glfwWindow(WIDTH,HEIGHT,"fps_move");
auto window = glfwWindow.getWindow();

MY_CAMERA::Camera camera;

void ProcessInput()
{
    static float lastFrame = 0.0f;
    float currentFrame = glfwGetTime();

    constexpr float speed = 0.5f;

    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    float cameraSpeed = speed * deltaTime;

    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);

    /**
     * @brief 
     * wasd
     */
    if(glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyBorad(MY_CAMERA::FRONT,cameraSpeed);
    if(glfwGetKey(window,GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyBorad(-MY_CAMERA::FRONT,cameraSpeed);
    if(glfwGetKey(window,GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyBorad(-MY_CAMERA::RIGHT,cameraSpeed);
    if(glfwGetKey(window,GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyBorad(MY_CAMERA::RIGHT,cameraSpeed);
    

    /**
     * @brief 
     * 上升和下降
     * 
     */

    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyBorad(MY_CAMERA::UP,cameraSpeed);
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyBorad(-MY_CAMERA::UP,cameraSpeed);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static float lastX = WIDTH/2;
    static float lastY = HEIGHT/2;
    static bool firstMouse = true;
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos-lastX;
    float yoffset = lastY-ypos;
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouse(glm::vec2(xoffset,yoffset));
}

int main()
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window,mouse_callback);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    BUFFER_OBJECT::VBO vbo;
    vbo.bind();
    vbo.setBufferData(sizeof(vertices),vertices, GL_STATIC_DRAW);

    BUFFER_OBJECT::VAO vao;
    vao.bind();
    BUFFER_OBJECT::VAO_LAYOUT layout;
    layout.push(3);
    layout.push(2);
    vao.setVertexAttribPointer(layout);

    MY_IMAGE::Texture texture("../assets/texture/container.jpg");
    texture.bind();

    MY_SHADER::Shader shader;
    shader.setVertexShaderByPath("../src/shader/fps.vert");
    shader.setFragmentShaderByPath("../src/shader/fps.frag");
    shader.linkShaderProgram();

    shader.use();
    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f),(float)WIDTH/(float)HEIGHT , 0.1f, 100.0f);
    shader.setMat4("projection",projection);
    while(!glfwWindowShouldClose(window))
    {
        ProcessInput();

        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 view = camera.getLookAt();
        shader.setMat4("view",view);

        for(int i=0 ;i <10;i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model,cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model,glm::radians(angle),glm::vec3(1.0f,0.3f,0.5f));
            shader.setMat4("model",model);

            glDrawArrays(GL_TRIANGLES,0,36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    return 0;
}