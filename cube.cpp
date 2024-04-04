//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cube.h"

void Cube::Draw(GLfloat g_vertex_buffer_data[]) {
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

