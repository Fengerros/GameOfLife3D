#pragma once

#include <unordered_map>
#include <string>
#include "../headers/VAO.hpp"
#include "../headers/VBO.hpp"
#include "../headers/EBO.hpp"

class VAOManager {
private:
    std::unordered_map<std::string, VAO> vaoMap;

public:
    VAO& getVAO(const std::string& name, const std::vector<float>& vertices, const std::vector<float>& tex_coords, const std::vector<float>& normals, const std::vector<unsigned short>& indices) {
        if (vaoMap.count(name) == 0) {
            // Tworzenie VAO dla danego bloku, jeśli jeszcze nie istnieje
            // Tutaj możesz użyć swojej logiki do tworzenia VAO dla konkretnych właściwości bloku
            // np. przekazując tablice vertices, indices, tex_coords itp.
            VAO newVAO;
            newVAO.Bind();

            VBO newVbo(vertices, sizeof(float) * vertices.size());
            VBO newTex(tex_coords, sizeof(float) * tex_coords.size());
            VBO newNorm(normals, sizeof(float) * normals.size());
            EBO newEbo(indices, sizeof(unsigned short) * indices.size());

            newVAO.LinkAttrib(newVbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
            newVAO.LinkAttrib(newTex, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);
            newVAO.LinkAttrib(newNorm, 2, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

            newVAO.Unbind();
            newVbo.Unbind();
            newTex.Unbind();
            newNorm.Unbind();
            newEbo.Unbind();

            // Dodanie VAO do mapy
            vaoMap[name] = newVAO;
        }

        return vaoMap[name];
    }
};
