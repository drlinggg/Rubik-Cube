//
// Created by User on 04.04.2024.
//

#ifndef LRCUBE_SHADER_H
#define LRCUBE_SHADER_H

#include <string>
#include <vector>


class Shader{
public:
    int id;
    Shader(int id);
    ~Shader();

    void use();
};

extern Shader* load_shader(std::string vertexFile, std::string FragmentFile);

#endif //LRCUBE_SHADER_H