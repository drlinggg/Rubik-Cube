//
// Created by Andrei Banakh on 04.04.2024.
//

#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#ifndef LRCUBE_SMALLCUBE_H
#define LRCUBE_SMALLCUBE_H

class smallCube{                               //кубик 1x1
private:
    float X;
    float Y;
    float Z;
    float faceLeftBottom[3];
    float faceRightBottom[3];
    float faceLeftUp[3];
    float faceRightUp[3];
    float backLeftBottom[3];
    float backRightBottom[3];
    float backLeftUp[3];
    float backRightUp[3];
    char sides[6] = {0,1,2,3,4,5};

public:

    void Draw(std::vector<Shader*> shaders);
    void Init();
    float GetX();
    float GetY();
    float GetZ();
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
};

#endif //LRCUBE_SMALLCUBE_H
