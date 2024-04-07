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
    GLfloat yaw = 0.0f;
    GLfloat pitch = -90.0f;
    GLfloat radius = 2;
    GLFWwindow* window;
    std::vector<Shader*> shaders;
    Cube br; //экземпляр куба
    void reCalc();
public:
    GLFWwindow* getWindow();
    void processInput();
    int init();
    void load();
    void save();
    void drawScene();
};


#endif //LRCUBE_CUBEDLG_H