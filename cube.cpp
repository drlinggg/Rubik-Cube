//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cube.h"

void Cube::Draw(std::vector<Shader*> shaders, glm::mat4 MVP) { //рисуем каждый кубик
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                bricks[x][y][z].Draw(shaders, MVP);
            }
        }
    }
}

void Cube::Init(const char *load = "default") { //устанавливаем центры кубиков относительно нашего
    X = Y = Z = 0;
    size = 1.0f;
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                bricks[x+1][y+1][z+1].SetX(float(x)*(size/3));
                bricks[x+1][y+1][z+1].SetY(float(y)*(size/3));
                bricks[x+1][y+1][z+1].SetZ(float(z)*(size/3));
                bricks[x+1][y+1][z+1].Init(size); //инициализируем их
            }
        }
    }
    if (strcmp(load, "default")) {
        FILE* loading_file = fopen(load, "r");
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    for (int side = 0; side < 6; side++) {
                        int curSide = getc(loading_file);
                        bricks[x][y][z].SetSide(side,curSide-48);
                    }
                }
            }
        }
        fclose(loading_file);
    }
}

void Cube::turnVer(int ver, int mode) { //свапаем кубики соответствующие после их поворотов вокруг оси //-1 вверх лол
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
            bricks[ver][2][0].SetSide(i, start.Side(i));
            bricks[ver][2][2].SetSide(i, fouth.Side(i));
            bricks[ver][0][0].SetSide(i, second.Side(i));
            bricks[ver][0][2].SetSide(i, third.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[ver][2][0].SetSide(i, third.Side(i));
            bricks[ver][0][2].SetSide(i, start.Side(i));
            bricks[ver][2][2].SetSide(i, second.Side(i));
            bricks[ver][0][0].SetSide(i, fouth.Side(i));
        }
    }
    start = bricks[ver][1][0];
    second = bricks[ver][0][1];
    third = bricks[ver][1][2];
    fouth = bricks[ver][2][1];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[ver][1][0].SetSide(i, second.Side(i));
            bricks[ver][0][1].SetSide(i, third.Side(i));
            bricks[ver][1][2].SetSide(i, fouth.Side(i));
            bricks[ver][2][1].SetSide(i, start.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[ver][1][0].SetSide(i, fouth.Side(i));
            bricks[ver][0][1].SetSide(i, start.Side(i));
            bricks[ver][1][2].SetSide(i, second.Side(i));
            bricks[ver][2][1].SetSide(i, third.Side(i));
        }
    }
}

void Cube::turnHor(int hor, int mode) { //свапаем кубики соответствующие после их поворотов вокруг оси
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
            bricks[0][hor][2].SetSide(i, start.Side(i));
            bricks[2][hor][2].SetSide(i, second.Side(i));
            bricks[2][hor][0].SetSide(i, third.Side(i));
            bricks[0][hor][0].SetSide(i, fouth.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[2][hor][0].SetSide(i,start.Side(i));
            bricks[2][hor][2].SetSide(i,fouth.Side(i));
            bricks[0][hor][0].SetSide(i,second.Side(i));
            bricks[0][hor][2].SetSide(i,third.Side(i));
        }
    }
    start = bricks[1][hor][0];
    second = bricks[0][hor][1];
    third = bricks[1][hor][2];
    fouth = bricks[2][hor][1];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[0][hor][1].SetSide(i,start.Side(i));
            bricks[1][hor][2].SetSide(i,second.Side(i));
            bricks[2][hor][1].SetSide(i,third.Side(i));
            bricks[1][hor][0].SetSide(i,fouth.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[2][hor][1].SetSide(i,start.Side(i));
            bricks[1][hor][0].SetSide(i,second.Side(i));
            bricks[0][hor][1].SetSide(i,third.Side(i));
            bricks[1][hor][2].SetSide(i,fouth.Side(i));
        }
    }
}

void Cube::turnThrough(int ver, int mode) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            bricks[x][y][ver].turndown();
            if (mode == -1) {
                bricks[x][y][ver].turnright();
            }
            else {
                bricks[x][y][ver].turnleft();
            }
            bricks[x][y][ver].turnup();
        }
    }
    smallCube start = bricks[0][0][ver];
    smallCube second = bricks[2][0][ver];
    smallCube third = bricks[2][2][ver];
    smallCube fouth = bricks[0][2][ver];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[2][0][ver].SetSide(i,start.Side(i));
            bricks[2][2][ver].SetSide(i,second.Side(i));
            bricks[0][2][ver].SetSide(i,third.Side(i));
            bricks[0][0][ver].SetSide(i,fouth.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[0][2][ver].SetSide(i,start.Side(i));
            bricks[2][2][ver].SetSide(i,fouth.Side(i));
            bricks[2][0][ver].SetSide(i,third.Side(i));
            bricks[0][0][ver].SetSide(i,second.Side(i));
        }
    }
    start = bricks[0][1][ver];
    second = bricks[1][2][ver];
    third = bricks[2][1][ver];
    fouth = bricks[1][0][ver];
    if (mode == -1) {
        for (int i = 0; i < 6; i++) {
            bricks[2][1][ver].SetSide(i,fouth.Side(i));
            bricks[1][2][ver].SetSide(i,third.Side(i));
            bricks[0][1][ver].SetSide(i,second.Side(i));
            bricks[1][0][ver].SetSide(i,start.Side(i));
        }
    }
    else {
        for (int i = 0; i < 6; i++) {
            bricks[1][2][ver].SetSide(i,start.Side(i));
            bricks[2][1][ver].SetSide(i,second.Side(i));
            bricks[1][0][ver].SetSide(i,third.Side(i));
            bricks[0][1][ver].SetSide(i,fouth.Side(i));
        }
    }
}