//
// Created by Andrei Banakh on 03.04.2024.
//
#include "smallCube.h"

#ifndef RUBIK_CUBE_CUBE_H
#define RUBIK_CUBE_CUBE_H

class Cube {                                                        //куб 3х3
private:
    smallCube bricks[3][3][3];
    float nSize;
    float nX;
    float nY;
    float nZ;
    float nDelta;
public:
    void turn(int idCubeFace, int mode); // mode -90 90 180 id 1-6
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
    void SetSize(float size);
    void SetDelta(float d);
    float GetX();
    float GetY();
    float GetZ();
    float GetSize();
    float GetDelta();

    void Draw();
    void Init();

    void al1(); // нижний крест
    void al2(); // нижний полный часть среднего
    void al3(); // два нижних слоя
    void al4(); // верхний крест
    void al5(); // угловые верх на свои места
    void al6(); // ориентация верхних угловых кубиков
};

#endif //RUBIK_CUBE_CUBE_H
