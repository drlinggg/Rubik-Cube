//
// Created by User on 04.04.2024.
//
#include "cube.cpp"

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

class CubeDlg {
private:
    GLFWwindow* window;
    GLfloat nXangle;
    GLfloat nYangle;
    GLfloat nZangle;
public:
    void init();
    void intermix();
    void load();
    void save();
    void drawScene();
    Cube br;                              //экземпляр куба
};

#endif //LRCUBE_CUBEDLG_H
