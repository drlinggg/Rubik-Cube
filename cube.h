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
    //char colorSides[54]; //front left back right bottom up

public:
    void turnHor(int hor, int mode);
    void turnVer(int ver, int mode);
    void turnThrough(int ver, int mode);
    void SetSize(float size);
    float GetSize();
    bool is_correct();
    void Draw(std::vector<Shader*> shaders, glm::mat4 MVP);
    void Init();

    smallCube bricks[3][3][3];
};

#endif //RUBIK_CUBE_CUBE_H