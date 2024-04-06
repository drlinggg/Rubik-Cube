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

//class shadersClass{
//public:
//    static std::vector<Shader*> shaders;
//    void load_shaders() {
//        shaders.resize(6);
//        shaders[0] = load_shader("../main.glslv", "../main.glslf");
//        shaders[1] = load_shader("../back.glslv", "../main.glslf");
//        shaders[2] = load_shader("../left.glslv", "../left.glslf");
//        shaders[3] = load_shader("../right.glslv", "../right.glslf");
//        shaders[4] = load_shader("../bottom.glslv", "../bottom.glslf");
//        shaders[5] = load_shader("../up.glslv", "../up.glslf");
//    }
//};

#endif //LRCUBE_SHADER_H