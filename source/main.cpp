#include "shaders.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>

const static int size_x = 800;
const static int size_y = 600;

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

struct VBO
{
    unsigned int id;
    VBO() {
        static constexpr float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    }
};

struct VShader
{
    unsigned int id;
    VShader()
    {
        id = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(id, 1, &vertexShader, NULL);
        glCompileShader(id);
    }
};
struct FShader
{
    unsigned int id;
    FShader()
    {
        id = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(id, 1, &fragmentShader, NULL);
        glCompileShader(id);
    }
};
struct ShaderProgram
{
    unsigned int id;
    ShaderProgram(unsigned int v, unsigned int f)
    {
        id = glCreateProgram();
        glAttachShader(id, v);
        glAttachShader(id, f);
        glLinkProgram(id);
        glUseProgram(id);
    }
};
struct VAO
{
    unsigned int id;
    VAO()
    {
        glGenVertexArrays(1, &id);
        glBindVertexArray(id);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(0);
    }
};

void render()
{
    //One time setup
    static VBO vbo;
    static VShader vshade;
    static FShader fshade;
    static ShaderProgram program(vshade.id, fshade.id);
    static VAO vao;

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
    }

    glfwTerminate();
    return 0;
}