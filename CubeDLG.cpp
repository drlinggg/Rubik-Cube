//
// Created by User on 04.04.2024.
//
#include "cubeDLG.h"
using namespace glm;

int CubeDlg::init() {
    nXangle = 0;
    nYangle = 0;
    nZangle = 0;

    //инициализация glfw
    if( !glfwInit() ){
        std::cout << "no glfw init";
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x Сглаживание
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Мы хотим использовать OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Мы не хотим старый OpenGL

    //создать окно
    window = glfwCreateWindow( 1200, 800, "Rubic Cube", NULL, NULL);
    if( window == NULL ){
        std::cout << "error window create";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //инициализация GLEW
    glewExperimental=true;                              // Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        std::cout << "no glew init";
        return -1;
    }
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    return 0;
}

void CubeDlg::drawScene() {
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glFinish();
    br.Draw();
    glfwSwapBuffers(window);
}