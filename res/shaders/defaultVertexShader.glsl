#version 460 core

layout (location = 0) in vec3 aPos;

vec3 aColor = vec3(1.0f, 0.0f, 0.0f);

out vec3 color;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = aColor;
}