//
// Created by Andrei Banakh on 03.04.2024.
//
#include "smallCube.h"

#ifndef RUBIK_CUBE_CUBE_H
#define RUBIK_CUBE_CUBE_H

class Cube {                                                        //куб 3х3
private:
    float X;
    float Z;
    float Y;
    float size;
    smallCube bricks[3][3][3];
    void al1(); // нижний крест
    void al2(); // нижний полный часть среднего
    void al3(); // два нижних слоя
    void al4(); // верхний крест
    void al5(); // угловые верх на свои места
    void al6(); // ориентация верхних угловых кубиков

public:
    void turnHor(int hor, int mode);
    void turnVer(int ver, int mode);
    void turnThrough(int ver, int mode);
    void SetSize(float size);
    float GetSize();
    void shuffle();
    bool is_correct();
    void solve();
    void Draw(std::vector<Shader*> shaders, glm::mat4 MVP);
    void Init();
};

#endif //RUBIK_CUBE_CUBE_H
