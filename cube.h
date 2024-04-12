//
// Created by Andrei Banakh on 03.04.2024.
//
#include "smallCube.h"

#ifndef RUBIK_CUBE_CUBE_H
#define RUBIK_CUBE_CUBE_H

class Cube {                                                        //куб 3х3
private:
    float X;
    float Z;
    float Y;
    float size;
public:
    void turnVer(int ver, int mode);
    void turnThrough(int ver, int mode);
    void Draw(std::vector<Shader*> shaders, glm::mat4 MVP);
    void Init(const char *load);
    smallCube bricks[3][3][3];
    void turnHor(int hor, int mode);
};

#endif //RUBIK_CUBE_CUBE_H
