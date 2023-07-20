#pragma once

#include <GL/glew.h>
#include <vector>

class EBO
{
    public:
        GLuint ID;

        EBO() : ID(0) {}
        EBO(std::vector<unsigned short> indices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
};