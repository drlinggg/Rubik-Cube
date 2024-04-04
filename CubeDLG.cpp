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
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    return 0;
}

void CubeDlg::drawScene() {
    std::vector<float> grani;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int z = 0; z < 3; z++) {
                grani.push_back(br.bricks[i][j][z].faceLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[2]);

                grani.push_back(br.bricks[i][j][z].faceLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[0]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[1]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[2]);

                grani.push_back(br.bricks[i][j][z].backLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].backRightUp[0]);
                grani.push_back(br.bricks[i][j][z].backRightUp[1]);
                grani.push_back(br.bricks[i][j][z].backRightUp[2]);

                grani.push_back(br.bricks[i][j][z].faceLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[2]);

                grani.push_back(br.bricks[i][j][z].faceLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[0]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[1]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[2]);
                grani.push_back(br.bricks[i][j][z].backRightUp[0]);
                grani.push_back(br.bricks[i][j][z].backRightUp[1]);
                grani.push_back(br.bricks[i][j][z].backRightUp[2]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[0]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[1]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[2]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[2]);

                grani.push_back(br.bricks[i][j][z].faceRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].backRightUp[0]);
                grani.push_back(br.bricks[i][j][z].backRightUp[1]);
                grani.push_back(br.bricks[i][j][z].backRightUp[2]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].backRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceRightBottom[2]);
                grani.push_back(br.bricks[i][j][z].backRightUp[0]);
                grani.push_back(br.bricks[i][j][z].backRightUp[1]);
                grani.push_back(br.bricks[i][j][z].backRightUp[2]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[0]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[1]);
                grani.push_back(br.bricks[i][j][z].faceRightUp[2]);

                grani.push_back(br.bricks[i][j][z].faceLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].backLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftBottom[2]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].backLeftUp[2]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[0]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[1]);
                grani.push_back(br.bricks[i][j][z].faceLeftUp[2]);
            }
        }
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLfloat g_vertex_buffer_data[grani.size()];
    for (int i = 0; i < grani.size(); i++) {
        g_vertex_buffer_data[i] = grani[i];
    }
    GLuint vertexbuffer;                                                                                                // Это будет идентификатором нашего буфера вершин
    glGenBuffers(1, &vertexbuffer);                                                                                     // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);                                                                        // Сделаем только что созданный буфер текущим
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);                  // Передадим информацию о вершинах в OpenGL
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void*)0            // Смещение массива в буфере
    );

    glDrawArrays(GL_TRIANGLES, 0, grani.size());
    glDisableVertexAttribArray(0);
    glfwSwapBuffers(window);
}