//
// Created by Andrei Banakh on 04.04.2024.
//
#include "cube.h"

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

class CubeDlg {
private:
    GLfloat x = 1;
    GLfloat y = 1;
    GLfloat z = 1;
    GLfloat degres = 90; //угол, причем не работает
public:
    GLFWwindow* window;
    std::vector<Shader*> shaders;
    int init();
    //void load();
    //void save();
    void drawScene(float x, float y, float z);
    Cube br;                              //экземпляр куба
};

#endif //LRCUBE_CUBEDLG_H
