#include "shaders.h"
#include "vertices.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <thread>

const static int size_x = 800;
const static int size_y = 600;

const static float timestep_ms = 15;

//window callbacks

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

//helper functions

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void render()
{
    //One time setup
    static ShaderProgram program(vertex_shader, fragment_shader);
    static VertexArrayObject vao(
        {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        },
        3);
    static bool first_time = true;
    if (first_time)
    {
        first_time = false;
        vao.add_vertex_attribute_pointer(0, 3, false, 0);
    }

    static float phase = 0.f;
    phase += timestep_ms / 1000;
    auto world_translate = glm::translate(glm::mat4(1.0f), glm::vec3(sinf(phase), sinf(phase), -3.f));
    auto world_rotate = glm::rotate(glm::mat4(1.0f), sinf(phase), glm::vec3(0.f, 1.f, 0.f));
    auto world = world_translate * world_rotate;

    auto view_translate = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -3.f));
    auto view_rotate = glm::rotate(glm::mat4(1.0f), 0.15f * sinf(phase), glm::vec3(1.f, 0.f, 0.f));
    auto view_perspective = glm::perspective(45.0f, 1.0f, 0.1f, 100.0f);
    auto view = view_perspective * view_rotate * view_translate;
    program.set_mat4("world", world);
    program.set_mat4("view", view);

    //Clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //Draw
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(size_x, size_y, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, size_x, size_y);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        render();

        glfwSwapBuffers(window);
        glfwPollEvents();

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(timestep_ms * 1ms);
    }

    glfwTerminate();
    return 0;
}