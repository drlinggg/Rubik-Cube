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

public:
    float faceLeftBottom[3];
    float faceRightBottom[3];
    float faceLeftUp[3];
    float faceRightUp[3];
    float backLeftBottom[3];
    float backRightBottom[3];
    float backLeftUp[3];
    float backRightUp[3];
    int color[6];
    void Draw(GLfloat g_vertex_buffer_data[]);
    void Init();
    float GetX();
    float GetY();
    float GetZ();
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
};

#endif //LRCUBE_SMALLCUBE_H
