//
// Created by Andrei Banakh on 04.04.2024.
//

#include "smallCube.h"
void smallCube::Draw(GLfloat g_vertex_buffer_data[]) {
}

void smallCube::Init() {
    faceLeftBottom[0] = GetX()-0.1; faceLeftBottom[1] = GetY()-0.1, faceLeftBottom[2] = GetZ()-0.1;
    faceRightBottom[0] = GetX()+0.1, faceRightBottom[1] = GetY()-0.1, faceRightBottom[2] = GetZ()-0.1;
    faceRightUp[0] = GetX() + 0.1, faceRightUp[1] = GetY()+0.1, faceRightUp[2] = GetZ()-0.1;
    faceLeftUp[0] = GetX() - 0.1, faceLeftUp[1] = GetY()+0.1, faceLeftUp[2] = GetZ()-0.1;
    backLeftBottom[0] = GetX()-0.1, backLeftBottom[1] = GetY()-0.1, backLeftBottom[2] = GetZ()+0.1;
    backRightBottom[0] =  GetX()+0.1, backRightBottom[1] = GetY()-0.1, backRightBottom[2] = GetZ()+0.1;
    backLeftUp[0] = GetX()-0.1, backLeftUp[1] = GetY()+0.1, backLeftUp[2] = GetZ()+0.1;
    backRightUp[0] = GetX() + 0.1, backRightUp[1] = GetY()+0.1, backRightUp[2] = GetZ()+0.1;
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