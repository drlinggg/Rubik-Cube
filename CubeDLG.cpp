//
// Created by Andrei Banakh on 04.04.2024.
//
#include "cubeDLG.h"
using namespace glm;

void CubeDlg::render(std::vector<float>& grani) {

}

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

    window = glfwCreateWindow( 1000, 1000, "Rubic Cube", NULL, NULL);  //создать окно
    if( window == NULL ){
        std::cout << "error window create";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    br.Init();


    glewExperimental=true;                              // инициализация GLEW, Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        std::cout << "no glew init";
        return -1;
    }

    shaders.resize(6);
        shaders[0] = load_shader("../main.glslv", "../main.glslf");
        shaders[1] = load_shader("../back.glslv", "../back.glslf");
        shaders[2] = load_shader("../left.glslv", "../left.glslf");
        shaders[3] = load_shader("../right.glslv", "../right.glslf");
        shaders[4] = load_shader("../up.glslv", "../up.glslf");
        shaders[5] = load_shader("../bottom.glslv", "../bottom.glslf");

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    return 0;
}

void CubeDlg::drawScene() {
    std::vector<float> grani;
    br.Draw(shaders);

    glDisableVertexAttribArray(0);
    glfwSwapBuffers(window);
}