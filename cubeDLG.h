//
// Created by Andrei Banakh on 04.04.2024.
//
#include "Cube.h"

#ifndef LRCUBE_CUBEDLG_H
#define LRCUBE_CUBEDLG_H

class CubeDlg {
private:
    glm::vec3 cam = glm::vec3(1,1,1);
    glm::vec2 angles = glm::vec2(0,0);
    int screenSize[2] = {1000,1000};
    GLfloat radius = 2;
    GLfloat turnSpeed = 30.0f;
    GLFWwindow* window; //экземпляр окна
    std::vector<Shader*> shaders;
    Cube br; //экземпляр куба
    void reCalc(); //пересчет координат камеры
    bool check_nn_cross();
    void assembling_cross();//Сборка креста
    bool check_cross();
    bool check_level1();
    bool check_level2();
    bool check_level3up();
    bool check_vertexlvl3();
    bool check_edgeslvl3();
    void changeSide();
    void turnHor(int hor, int mode);
    void turnThrough(int ver, int mode);
    void turnVer(int ver, int mode);
    void FF();
    void SF();
    void CRUP();
    void CRUP2();
    void vertexlvl3();
    void edgelvl3();
    void solve();
    void pifpaf1();
    void pifpaf2();
    void leftpifpaf();
public:
    GLFWwindow* getWindow();
    void shuffle(int countOperations);
    void processInput();
    int init();
    void load(const char *file);
    void save(const char *file);
    void drawScene();
};


#endif //LRCUBE_CUBEDLG_H
