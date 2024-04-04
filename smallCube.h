//
// Created by Andrei Banakh on 04.04.2024.
//

#include "color.h"

#ifndef LRCUBE_SMALLCUBE_H
#define LRCUBE_SMALLCUBE_H

class smallCube{                               //кубик 1x1
private:
    float X;
    float Y;
    float Z;
    float nXangle;
    float nYangle;
    float nZangle;

    //cColor vertexs[3];
public:
    void Draw(GLfloat g_vertex_buffer_data[]);
    void Init(float x, float y, float z);
    float GetX();
    float GetY();
    float GetZ();
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
};

#endif //LRCUBE_SMALLCUBE_H
