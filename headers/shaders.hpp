#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>

class Shaders
{
private:
    
public:
    GLuint ID;

    void CreateProgram(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    void Activate();
    void Delete();
};
