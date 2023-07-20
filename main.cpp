#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "headers/shaders.hpp"
#include "headers/VAO.hpp"
#include "headers/VAOManager.hpp"
#include "headers/camera.hpp"

std::string window_title = "GameOfLife3D";

unsigned int window_width = 1100;
unsigned int window_height = 600;

bool isCameraMovement = true;
bool firstMouse = true;

GLFWwindow *window;

struct Timer
{
    float last_frame = 0.0f;
    float delta_time = 0.0f;
    float current_frame;
};

void processInput(GLFWwindow *window);

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

    // timer init
    Timer timer;

    std::vector<float> vertices = {
        // cube vertices
        // front face
        -0.5f, -0.5f, 0.5f, // 0
        0.5f, -0.5f, 0.5f,  // 1
        0.5f, 0.5f, 0.5f,   // 2
        -0.5f, 0.5f, 0.5f,  // 3

        // right face
        0.5f, -0.5f, 0.5f,  // 4
        0.5f, -0.5f, -0.5f, // 5
        0.5f, 0.5f, -0.5f,  // 6
        0.5f, 0.5f, 0.5f,   // 7

        // back face
        -0.5f, -0.5f, -0.5f, // 8
        0.5f, -0.5f, -0.5f,  // 9
        0.5f, 0.5f, -0.5f,   // 10
        -0.5f, 0.5f, -0.5f,  // 11

        // left face
        -0.5f, -0.5f, -0.5f, // 12
        -0.5f, -0.5f, 0.5f,  // 13
        -0.5f, 0.5f, 0.5f,   // 14
        -0.5f, 0.5f, -0.5f,  // 15

        // bottom face
        -0.5f, -0.5f, 0.5f,  // 16
        0.5f, -0.5f, 0.5f,   // 17
        0.5f, -0.5f, -0.5f,  // 18
        -0.5f, -0.5f, -0.5f, // 19

        // top face
        -0.5f, 0.5f, 0.5f,  // 20
        0.5f, 0.5f, 0.5f,   // 21
        0.5f, 0.5f, -0.5f,  // 22
        -0.5f, 0.5f, -0.5f, // 23
    };

    std::vector<unsigned short> indices = {
        0, 1, 2,
        2, 3, 0,

        // right face
        4, 5, 6,
        6, 7, 4,

        // back face
        10, 9, 8,
        8, 11, 10,

        12, 13, 14,
        14, 15, 12,

        // bottom face
        18, 17, 16,
        16, 19, 18,

        // top face
        20, 21, 22,
        22, 23, 20
    };


    std::vector<float> tex_coords = {
        // front face
        0.0f, 0.0f, // 0
        1.0f, 0.0f, // 1
        1.0f, 1.0f, // 2
        0.0f, 1.0f, // 3

        // right face
        0.0f, 0.0f, // 4
        1.0f, 0.0f, // 5
        1.0f, 1.0f, // 6
        0.0f, 1.0f, // 7

        // back face
        0.0f, 0.0f, // 8
        1.0f, 0.0f, // 9
        1.0f, 1.0f, // 10
        0.0f, 1.0f, // 11

        // left face
        0.0f, 0.0f, // 12
        1.0f, 0.0f, // 13
        1.0f, 1.0f, // 14
        0.0f, 1.0f, // 15

        // bottom face
        0.0f, 0.0f, // 16
        1.0f, 0.0f, // 17
        1.0f, 1.0f, // 18
        0.0f, 1.0f, // 19

        // top face
        0.0f, 0.0f, // 20
        1.0f, 0.0f, // 21
        1.0f, 1.0f, // 22
        0.0f, 1.0f  // 23
    };

    std::vector<float> normals = {
        // front face
        0.0f, 0.0f, 1.0f, // 0
        0.0f, 0.0f, 1.0f, // 1
        0.0f, 0.0f, 1.0f, // 2
        0.0f, 0.0f, 1.0f, // 3

        // right face
        1.0f, 0.0f, 0.0f, // 4
        1.0f, 0.0f, 0.0f, // 5
        1.0f, 0.0f, 0.0f, // 6
        1.0f, 0.0f, 0.0f, // 7

        // back face
        0.0f, 0.0f, -1.0f, // 8
        0.0f, 0.0f, -1.0f, // 9
        0.0f, 0.0f, -1.0f, // 10
        0.0f, 0.0f, -1.0f, // 11

        // left face
        -1.0f, 0.0f, 0.0f, // 12
        -1.0f, 0.0f, 0.0f, // 13
        -1.0f, 0.0f, 0.0f, // 14
        -1.0f, 0.0f, 0.0f, // 15

        // bottom face
        0.0f, -1.0f, 0.0f, // 16
        0.0f, -1.0f, 0.0f, // 17
        0.0f, -1.0f, 0.0f, // 18
        0.0f, -1.0f, 0.0f, // 19

        // top face
        0.0f, 1.0f, 0.0f, // 20
        0.0f, 1.0f, 0.0f, // 21
        0.0f, 1.0f, 0.0f, // 22
        0.0f, 1.0f, 0.0f  // 23
    };

    VAOManager vaoManager;

    VAO cell_vao;
    cell_vao = vaoManager.getVAO("cell", vertices, tex_coords, normals, indices);
    cell_vao.Bind();

    // camera
    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    GLuint projectionLoc = glGetUniformLocation(default_shader.ID, "projection");
    GLuint viewLoc = glGetUniformLocation(default_shader.ID, "view");
    GLuint modelLoc = glGetUniformLocation(default_shader.ID, "model");
    
    float lastX = window_width / 2.0f;
    float lastY = window_height / 2.0f;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_CULL_FACE);  
    glCullFace(GL_BACK);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        processInput(window);
        
        glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timer.current_frame = glfwGetTime();
        timer.delta_time = timer.current_frame - timer.last_frame;
        timer.last_frame = timer.current_frame;

        default_shader.Activate();

        // start of camera part
        if (glfwGetWindowAttrib(window, GLFW_FOCUSED) == 0)
        {
            // relase coursor from app
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            isCameraMovement = false;
            firstMouse = true;
        }
        else
        {
            // if mouse left presed
            if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            {
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                // last position of cursor
                isCameraMovement = true;
                // prevent camera from jumping when first entering window
                if (firstMouse)
                {
                    double xpos, ypos;
                    glfwGetCursorPos(window, &xpos, &ypos);
                    lastX = xpos;
                    lastY = ypos;
                    firstMouse = false;
                }
            }
        }

        if (isCameraMovement)
        {
            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(FORWARD, timer.delta_time);
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(BACKWARD, timer.delta_time);
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(LEFT, timer.delta_time);
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(RIGHT, timer.delta_time);
            }
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(UP, timer.delta_time);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(DOWN, timer.delta_time);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
            {
                camera.ProcessKeyboard(SPRINT, timer.delta_time);
            }

            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;

            lastX = xpos;
            lastY = ypos;

            camera.ProcessMouseMovement(xoffset, yoffset);
        }

        glm::mat4 projection = glm::perspective(glm::radians(75.0f), (float)window_width / (float)window_height, 0.1f, 100.0f);

        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 model = glm::mat4(1.0f);

        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
        // end of camera part

        cell_vao.Bind();
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();    
    }
    glfwTerminate();

    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
    {
        glPointSize(2);
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    if (glfwGetKey(window, GLFW_KEY_F5) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}