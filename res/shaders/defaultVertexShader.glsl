#version 460 core

layout (location = 0) in vec3 aPos;

layout (location = 2) in vec3 aNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

vec3 aColor = vec3(0.9f, 0.9f, 0.2f);

out vec3 color;

out vec3 normal;

void main()
{
    mat4 MVP = projection * view * model;
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    color = aColor;
    normal = aNormal;
}