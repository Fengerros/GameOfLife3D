#include "../headers/shaders.hpp"

void Shaders::CreateProgram(const std::string &vertexShaderPath, const std::string &fragmentShaderPath)
{
    // Read vertex shader source code
    std::ifstream vertexShaderFile(vertexShaderPath);
    std::stringstream vertexShaderStream;
    vertexShaderStream << vertexShaderFile.rdbuf();
    std::string vertexShaderCode = vertexShaderStream.str();
    vertexShaderFile.close();

    // Read fragment shader source code
    std::ifstream fragmentShaderFile(fragmentShaderPath);
    std::stringstream fragmentShaderStream;
    fragmentShaderStream << fragmentShaderFile.rdbuf();
    std::string fragmentShaderCode = fragmentShaderStream.str();
    fragmentShaderFile.close();

    // Compile vertex shader
    const char *vertexShaderSource = vertexShaderCode.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    // Check for vertex shader compilation errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cerr << "Failed to compile vertex shader\n";
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << infoLog << '\n';
    }

    // Compile fragment shader
    const char *fragmentShaderSource = fragmentShaderCode.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    // Check for fragment shader compilation errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::cerr << "Failed to compile fragment shader\n";
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << infoLog << '\n';
    }

    // Create shader program
    GLuint shaderProgram = glCreateProgram();

    // Attach shaders to program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Link program
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        std::cerr << "Failed to link shader program\n";
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << infoLog << '\n';

        // Delete shaders
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return;
    }

    // Delete shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    ID = shaderProgram;
}

void Shaders::Activate()
{
    glUseProgram(ID);
}

void Shaders::Delete()
{
    glDeleteProgram(ID);
}