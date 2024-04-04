//
// Created by Andrei Banakh on 04.04.2024.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#ifndef LRCUBE_COLOR_H
#define LRCUBE_COLOR_H


class cColor {                             //цвет кубика 1x1
private:
    float X;
    float Y;
    float Z;
    float nXangle;
    float nYangle;
    float nZangle;

public:
    void Draw(GLfloat g_vertex_buffer_data[]);
    void Init(float x, float y, float z);
};

#endif //LRCUBE_COLOR_H
