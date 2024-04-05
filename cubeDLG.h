//
// Created by Andrei Banakh on 04.04.2024.
//
#include "cube.h"

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

class CubeDlg {
private:
    GLfloat nXangle;
    GLfloat nYangle;
    GLfloat nZangle;
public:
    GLFWwindow* window;
    std::vector<Shader*> shaders;
    int init();
    //void intermix();
    //void load();
    //void save();
    void render(std::vector<float>& grani);
    void drawScene();
    Cube br;                              //экземпляр куба
};

#endif //LRCUBE_CUBEDLG_H
