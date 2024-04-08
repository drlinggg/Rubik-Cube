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

void Cube::Init() { //устанавливаем центры кубиков относительно нашего
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
    //for (int pos = 0; pos < 54; pos++) {
    //colorSides[pos] = pos / 9;
    //}
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

void Cube::SetSize(float size) {
    this->size = size;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                bricks[x][y][z].Init(size);
            }
        }
    }
}

float Cube::GetSize() { //useless
    return size;
}

void Cube::solve() {
    assembling_cross();//Сборка неправильного креста
    F2L();
    OLL();
    PLL();
}

void Cube::assembling_cross() { //front left back right bottom up
    for (int k = 0; k < 40; k++) {
        if (bricks[1][2][0].Side(0) != 0 && bricks[1][2][0].Side(5) == 5 ||
            bricks[0][2][1].Side(1) != 1 && bricks[0][2][1].Side(5) == 5 ||
            bricks[1][2][2].Side(2) != 2 && bricks[1][2][2].Side(5) == 5 ||
            bricks[2][2][1].Side(3) != 3 && bricks[2][2][1].Side(5) == 5) {
            while (true) {
                turnHor(2, -1);
                if (bricks[1][2][0].Side(0) == 0 && bricks[1][2][0].Side(5) == 5 ||
                    bricks[0][2][1].Side(1) == 1 && bricks[0][2][1].Side(5) == 5 ||
                    bricks[1][2][2].Side(2) == 2 && bricks[1][2][2].Side(5) == 5 ||
                    bricks[2][2][1].Side(3) == 3 && bricks[2][2][1].Side(5) == 5) {
                    break;
                }
            }
        }
        //    frontSide;
        if (bricks[0][1][0].Side(0) == 5) {
            if (bricks[0][2][1].Side(5) == 5) {
                turnHor(2, -1);
                turnVer(0, -1);
                turnHor(2, 1);
            }
            else {
                turnVer(0, -1);
            }
        }

        if (bricks[2][1][0].Side(0) == 5) {
            if (bricks[2][2][1].Side(5) == 5) {
                turnHor(2, 1);
                turnVer(2, -1);
                turnHor(2, -1);
            }
            else {
                turnVer(2, -1);
            }
        }
        if (bricks[1][2][0].Side(0) == 5) {
            if (bricks[0][2][1].Side(5) != 5) {
                turnThrough(0, 1);
                turnVer(2, -1);
            }
            else {
                turnThrough(0, -1);
                turnVer(0, -1);
            }
        }
        if (bricks[1][0][0].Side(0) == 5) {
            if (bricks[0][2][1].Side(5) != 5) {
                turnThrough(0, 1);
                turnVer(0, -1);
            }
            else {
                turnThrough(0, -1);
                turnVer(2, -1);
            }
        }
        //backSide;
        if (bricks[0][1][2].Side(2) == 5) {
            if (bricks[0][2][1].Side(5) == 5) {
                turnHor(2, -1);
                turnVer(0, 1);
                turnHor(2, 1);
            }
            else {
                turnVer(0, 1);
            }
        }

        if (bricks[2][1][2].Side(2) == 5) {
            if (bricks[2][2][1].Side(5) == 5) {
                turnHor(2, -1);
                turnVer(2, 1);
                turnHor(2, 1);
            }
            else {
                turnVer(2, 1);
            }
        }
        if (bricks[1][2][2].Side(2) == 5) {
            if (bricks[0][2][1].Side(5) != 5) {
                turnThrough(2, -1);
                turnVer(0, 1);
            }
            else {
                turnThrough(2, 1);
                turnVer(2, 1);
            }
        }
        if (bricks[1][0][2].Side(2) == 5) {
            if (bricks[0][2][1].Side(5) != 5) {
                turnThrough(2, -1);
                turnVer(0, 1);
            }
            else {
                turnThrough(2, 1);
                turnVer(2, 1);
            }
        }
//        left  нижний слой ошибка
        if (bricks[0][1][0].Side(1) == 5) {
            if (bricks[1][2][0].Side(5) == 5) {
                turnHor(2, -1);
                turnThrough(0, 1);
                turnHor(2, 1);
            }
            else {
                turnThrough(0, 1);
            }
        }

        if (bricks[0][1][2].Side(1) == 5) {
            if (bricks[1][2][2].Side(5) == 5) {
                turnHor(2, 1);
                turnThrough(2, 1);
                turnHor(2, -1);
            }
            else {
                turnThrough(2, 1);
            }
        }
        if (bricks[0][2][1].Side(1) == 5) {
            if (bricks[1][2][2].Side(5) == 5) {
                turnVer(0, 1);
                turnThrough(2, 1);
            }
            else {
                turnVer(0, -1);
                turnThrough(0, 1);
            }
        }
        if (bricks[0][1][0].Side(1) == 5) {
            if (bricks[1][2][0].Side(5) != 5) {
                turnVer(0, -1);
                turnThrough(0,1);
            }
            else if (bricks[1][2][2].Side(5) != 5){
                turnVer(0,1);
                turnThrough(2, 1);
            }
            else {
                turnHor(0,1);

            }
        }
        //right
        if (bricks[2][1][0].Side(3) == 5) {
            if (bricks[1][2][0].Side(5) == 5) {
                turnHor(2, -1);
                turnThrough(0, 1);
                turnHor(2, 1);
            }
            else {
                turnThrough(0, 1);
            }
        }

        if (bricks[2][1][2].Side(3) == 5) {
            if (bricks[1][2][2].Side(5) == 5) {
                turnHor(2, 1);
                turnThrough(2, 1);
                turnHor(2, -1);
            }
            else {
                turnThrough(2, 1);
            }
        }
        if (bricks[2][2][1].Side(3) == 5) {
            if (bricks[1][2][2].Side(5) == 5) {
                turnVer(0,1);
                turnThrough(0,-1);
            }
            else {
                turnVer(0, -1);
                turnThrough(2, -1);
            }
        }
        if (bricks[2][0][1].Side(3) == 5) {
            if (bricks[1][2][0].Side(5) != 5) {
                turnVer(0, -1);
                turnThrough(0,-1);
            }
            else if (bricks[1][2][2].Side(5) != 5){
                turnVer(0,1);
                turnThrough(2, -1);
            }
            else {
                turnHor(0,1);

            }
        }
        if (bricks[1][0][0].Side(4) == 5) {
            if (bricks[1][2][0].Side(5) != 5) {
                turnThrough(0, 1);
                turnThrough(0, 1);
            }
            else {
                turnThrough(0,1);
                turnHor(1,1);
            }
        }
        if (bricks[0][0][1].Side(4) == 5) {
            if (bricks[0][2][1].Side(5) != 5) {
                turnVer(0, 1);
                turnVer(0, 1);
            }
            else {
                turnVer(0, 1);
                turnHor(1,1);
            }
        }
        if (bricks[1][0][2].Side(4) == 5) {
            if (bricks[1][2][2].Side(5) != 5) {
                turnThrough(2, 1);
                turnThrough(2, 1);
            }
            else {
                turnVer(0, 1);
                turnHor(1,1);
            }
        }
        if (bricks[2][0][1].Side(4) == 5) {
            if (bricks[2][2][1].Side(5) != 5){
                turnVer(2,1);
                turnVer(2,1);
            }
            else {
                turnVer(2,1);
                turnHor(1,1);
            }
        }
        turnHor(0,-1);
    }
}


void Cube::F2L() {

}

void Cube::OLL() {

}

void Cube::PLL() {

}


bool Cube::check_nn_cross() {
    int check = 0;
    (bricks[0][0][1].Side(5) == 5 ? check++ : NULL);
    (bricks[1][0][0].Side(5) == 5 ? check++ : NULL);
    (bricks[1][0][2].Side(5) == 5 ? check++ : NULL);
    (bricks[2][0][1].Side(5) == 5 ? check++ : NULL);
    if (check == 4) {
        return true;
    }
    return false;
}