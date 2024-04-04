//
// Created by Andrei Banakh on 04.04.2024.
//

#include "smallCube.h"
void smallCube::Draw(GLfloat g_vertex_buffer_data[]) {
}

void smallCube::Init() {
    colorSide.push_back(1.0f);
    colorSide.push_back(0.5f);
    colorSide.push_back(0.3f);
    colorSide.push_back(0.7f);
    colorSide.push_back(0.2f);
    colorSide.push_back(0.9f);

    faceLeftBottom[0] = GetX()-0.09; faceLeftBottom[1] = GetY()-0.09, faceLeftBottom[2] = GetZ()-0.09;
    faceRightBottom[0] = GetX()+0.09, faceRightBottom[1] = GetY()-0.09, faceRightBottom[2] = GetZ()-0.09;
    faceRightUp[0] = GetX() + 0.09, faceRightUp[1] = GetY()+0.09, faceRightUp[2] = GetZ()-0.09;
    faceLeftUp[0] = GetX() - 0.09, faceLeftUp[1] = GetY()+0.09, faceLeftUp[2] = GetZ()-0.09;
    backLeftBottom[0] = GetX()-0.09, backLeftBottom[1] = GetY()-0.09, backLeftBottom[2] = GetZ()+0.09;
    backRightBottom[0] =  GetX()+0.09, backRightBottom[1] = GetY()-0.09, backRightBottom[2] = GetZ()+0.09;
    backLeftUp[0] = GetX()-0.09, backLeftUp[1] = GetY()+0.09, backLeftUp[2] = GetZ()+0.09;
    backRightUp[0] = GetX() + 0.09, backRightUp[1] = GetY()+0.09, backRightUp[2] = GetZ()+0.09;
}

float smallCube::GetX() {
    return X;
}
float smallCube::GetY() {
    return Y;
}

float smallCube::GetZ() {
    return Z;
}

void smallCube::SetX(float x) {
    X = x;
}

void smallCube::SetY(float y) {
    Y = y;
}

void smallCube::SetZ(float z) {
    Z = z;
}