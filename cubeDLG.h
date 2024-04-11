//
// Created by Andrei Banakh on 04.04.2024.
//
#include "Cube.h"

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

class CubeDlg {
private:
    GLfloat x = 1;
    GLfloat y = 1;
    GLfloat z = 1;
    GLfloat angleHor;
    GLfloat angleVer;
    GLfloat radius = 2;
    GLFWwindow* window;
    std::vector<Shader*> shaders;
    Cube br; //экземпляр куба
    void reCalc();
    bool check_nn_cross();
    void assembling_cross();//Сборка неправильного креста
    bool check_cross();
    bool check_level1();
    void turnHor(int hor, int mode);
    void turnThrough(int ver, int mode);
    void turnVer(int ver, int mode);
    void FF();
    void SF();
    void CRDOWN();
    void solve();
    void pifpaf1();
    void pifpaf2();
public:
    GLFWwindow* getWindow();
    void shuffle(int countOperations);
    void processInput();
    int init();
    void load();
    void save();
    void drawScene();

};


#endif //LRCUBE_CUBEDLG_H