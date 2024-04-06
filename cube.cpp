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

