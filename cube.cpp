//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cube.h"

void Cube::Draw(std::vector<Shader*> shaders) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                bricks[x][y][z].Draw(shaders);
            }
        }
    }
}

void Cube::Init() {
    for (int x = -1; x < 2; x++) {
        for (int y = -1; y < 2; y++) {
            for (int z = -1; z < 2; z++) {
                bricks[x+1][y+1][z+1].SetX(float(x)*0.2);
                bricks[x+1][y+1][z+1].SetY(float(y)*0.2);
                bricks[x+1][y+1][z+1].SetZ(float(z)*0.2);
                bricks[x+1][y+1][z+1].Init();
            }
        }
    }
}

