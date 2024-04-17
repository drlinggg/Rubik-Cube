//
// Created by Andrei Banakh on 03.04.2024.
//
#include "smallCube.h"

#ifndef RUBIK_CUBE_CUBE_H
#define RUBIK_CUBE_CUBE_H

class Cube {                                                        //куб 3х3
private:
    glm::vec3 coords = glm::vec3(0,0,0);
    float size;
public:
    smallCube bricks[3][3][3];
    void turnVer(int ver, int mode);
    void turnThrough(int ver, int mode);
    void turnHor(int hor, int mode);
    void Draw(std::vector<Shader*> shaders, glm::mat4 MVP);
    void Init(const char *load);
    glm::vec3 getCoords();
};

#endif //RUBIK_CUBE_CUBE_H
