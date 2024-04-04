//
// Created by User on 04.04.2024.
//
#include "cube.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

class CubeDlg {
private:
    GLfloat nXangle;
    GLfloat nYangle;
    GLfloat nZangle;
public:
    GLFWwindow* window;
    int init();
    //void intermix();
    //void load();
    //void save();
    void drawScene();
    Cube br;                              //экземпляр куба
};

#endif //LRCUBE_CUBEDLG_H
