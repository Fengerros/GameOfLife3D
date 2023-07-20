#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "headers/shaders.hpp"

std::string window_title = "GameOfLife3D";

unsigned int window_width = 1100;
unsigned int window_height = 600;

GLFWwindow *window;

struct Timer
{
    float last_frame = 0.0f;
    float delta_time = 0.0f;
    float current_frame;
};


int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(window_width, window_height, window_title.c_str(), nullptr, nullptr);

    if (window == nullptr) {
        std::cout << "GLFW window error\n";
        glfwTerminate();
        std::cin.get();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK){
        std::cout << "GLEW init error\n";
        std::cin.get();
        return -1;
    }

    glViewport(0, 0, window_width, window_height);

    //shaders...
    Shaders default_shader;
    default_shader.CreateProgram("res/shaders/defaultVertexShader.glsl", "res/shaders/defaultFragmentShader.glsl");
    default_shader.Activate();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // timer init
    Timer timer;

    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glClearColor(0.1f, 1.0f, 0.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timer.current_frame = glfwGetTime();
        timer.delta_time = timer.current_frame - timer.last_frame;
        timer.last_frame = timer.current_frame;

        default_shader.Activate();

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();

    return 0;
}