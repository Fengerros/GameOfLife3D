#version 460 core

out vec4 FragColor;

in vec3 color;

in vec3 normal;

void main()
{ 
    vec3 lightDir = normalize(vec3(0.5, 0.9, 0.5));
    float diff = max(dot(normal, lightDir), 0.2);
    vec3 diffuse = vec3(1.0, 1.0, 1.0) * diff;

    // ambient
    vec3 ambient = vec3(0.3843, 0.3882, 0.3882);

    vec3 aColor = (ambient + diffuse) * (color);
    
    FragColor = vec4(aColor, 1.0);
}