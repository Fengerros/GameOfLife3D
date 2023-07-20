#pragma once

#include <GL/glew.h>
#include <vector>

class VBO
{
    public:
        GLuint ID;
        
        VBO() : ID(0) {}
        VBO(std::vector<float> vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};