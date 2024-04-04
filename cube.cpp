//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cube.h"

void Cube::Draw() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int z = 0; z < 3; z++) {
                bricks[i][j][z].Draw();
            }
        }
    }
}

