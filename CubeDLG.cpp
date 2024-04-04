//
// Created by User on 04.04.2024.
//

#include "cubeDLG.h"

void CubeDlg::drawScene() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -10.0f);
    glRotatef(nXangle, 1.0f, 0.0f, 0.0f);
    glRotatef(nYangle, 0.0f, 1.0f, 0.0f);
    glRotatef(nZangle, 0.0f, 0.0f, 1.0f);

    br.Draw();
    glFinish();
    SwapBuffers(window);
}

void CubeDlg::init() {
    nXangle = 0;
    nYangle = 0;
    nZangle = 0;
}