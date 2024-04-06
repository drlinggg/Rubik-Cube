//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cube.h"

void Cube::SetSize(float size) { //fix it, no connect with small bricks
    this->size = size;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                bricks[x][y][z].Init();
            }
        }
    }
}

float Cube::GetSize() { //useless
    return size;
}

void Cube::Draw(std::vector<Shader*> shaders, glm::mat4 MVP) { //рисуем каждый кубик
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                bricks[x][y][z].Draw(shaders, MVP);
            }
        }
    }
}

void Cube::Init() { //устанавливаем центры кубиков относительно нашего
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                bricks[x+1][y+1][z+1].SetX(float(x)*(size/3));
                bricks[x+1][y+1][z+1].SetY(float(y)*(size/3));
                bricks[x+1][y+1][z+1].SetZ(float(z)*(size/3));
                bricks[x+1][y+1][z+1].Init(); //инициализируем их
            }
        }
    }
}

void Cube::turnVer(int ver, int mode) {
    for (int y = 0; y < 3; y++) {
        for (int z = 0; z < 3; z++) {
            if (mode == -1) {
                bricks[ver][y][z].turndown();
            }
            else {
                bricks[ver][y][z].turnup();
            }
        }
    }
    smallCube start = bricks[ver][0][0];
    smallCube second = bricks[ver][0][2];
    smallCube third = bricks[ver][2][2];
    smallCube fouth = bricks[ver][2][0];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[ver][0][2].sides[i] = start.sides[i];
            bricks[ver][2][2].sides[i] = second.sides[i];
            bricks[ver][2][0].sides[i] = third.sides[i];
            bricks[ver][0][0].sides[i] = fouth.sides[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[ver][2][0].sides[i] = start.sides[i];
            bricks[ver][2][2].sides[i] = fouth.sides[i];
            bricks[ver][0][0].sides[i] = second.sides[i];
            bricks[ver][0][2].sides[i] = third.sides[i];
        }
    }
    start = bricks[ver][1][0];
    second = bricks[ver][0][1];
    third = bricks[ver][1][2];
    fouth = bricks[ver][2][1];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[ver][1][0].sides[i] = second.sides[i];
            bricks[ver][0][1].sides[i] = third.sides[i];
            bricks[ver][1][2].sides[i] = fouth.sides[i];
            bricks[ver][2][1].sides[i] = start.sides[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[ver][1][0].sides[i] = fouth.sides[i];
            bricks[ver][0][1].sides[i] = start.sides[i];
            bricks[ver][1][2].sides[i] = second.sides[i];
            bricks[ver][2][1].sides[i] = third.sides[i];
        }
    }
}

void Cube::turnHor(int hor, int mode) {
    for (int x = 0; x < 3; x++) {
        for (int z = 0; z < 3; z++) {
            if (mode == -1) {
                bricks[x][hor][z].turnleft();
            }
            else {
                bricks[x][hor][z].turnright();
            }
        }
    }
    smallCube start = bricks[0][hor][0];
    smallCube second = bricks[0][hor][2];
    smallCube third = bricks[2][hor][2];
    smallCube fouth = bricks[2][hor][0];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[0][hor][2].sides[i] = start.sides[i];
            bricks[2][hor][2].sides[i] = second.sides[i];
            bricks[2][hor][0].sides[i] = third.sides[i];
            bricks[0][hor][0].sides[i] = fouth.sides[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[2][hor][0].sides[i] = start.sides[i];
            bricks[2][hor][2].sides[i] = fouth.sides[i];
            bricks[0][hor][0].sides[i] = second.sides[i];
            bricks[0][hor][2].sides[i] = third.sides[i];
        }
    }
    start = bricks[1][hor][0];
    second = bricks[0][hor][1];
    third = bricks[1][hor][2];
    fouth = bricks[2][hor][1];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[0][hor][1].sides[i] = start.sides[i];
            bricks[1][hor][2].sides[i] = second.sides[i];
            bricks[2][hor][1].sides[i] = third.sides[i];
            bricks[1][hor][0].sides[i] = fouth.sides[i];
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[2][hor][1].sides[i] = start.sides[i];
            bricks[1][hor][0].sides[i] = second.sides[i];
            bricks[0][hor][1].sides[i] = third.sides[i];
            bricks[1][hor][2].sides[i] = fouth.sides[i];
        }
    }
}
