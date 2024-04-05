//
// Created by Andrei Banakh on 04.04.2024.
//

#include "smallCube.h"

void smallCube::Draw(std::vector<Shader*>shaders) {
    std::vector<float> grani;
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightUp[i]);
    }
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLfloat g_vertex_buffer_data[grani.size()];
    for (int gran = 0; gran < grani.size(); gran++) {
        g_vertex_buffer_data[gran] = grani[gran];
    }
    GLuint vertexbuffer;// Это будет идентификатором нашего буфера вершин
    glGenBuffers(1, &vertexbuffer);                                                                                     // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);                                                                        // Сделаем только что созданный буфер текущим
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);                  // Передадим информацию о вершинах в OpenGL
    glEnableVertexAttribArray(0);
    //shaders[this->sides[0]].use();
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
    0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
    3,                  // Размер
    GL_FLOAT,           // Тип
    GL_FALSE,           // Указывает, что значения не нормализованы
    0,                  // Шаг
    (void*)0            // Смещение массива в буфере
    );
    shaders[sides[1]]->use();
    glDrawArrays(GL_TRIANGLES, 0, grani.size());
//    grani.push_back(backLeftUp[0]);
//    grani.push_back(backLeftUp[1]);
//    grani.push_back(backLeftUp[2]);
//    grani.push_back(backLeftBottom[0]);
//    grani.push_back(backLeftBottom[1]);
//    grani.push_back(backLeftBottom[2]);
//    grani.push_back(backRightBottom[0]);
//    grani.push_back(backRightBottom[1]);
//    grani.push_back(backRightBottom[2]);
//    grani.push_back(backLeftUp[0]);
//    grani.push_back(backLeftUp[1]);
//    grani.push_back(backLeftUp[2]);
//    grani.push_back(backLeftBottom[0]);
//    grani.push_back(backLeftBottom[1]);
//    grani.push_back(backLeftBottom[2]);
//    grani.push_back(backRightUp[0]);
//    grani.push_back(backRightUp[1]);
//    grani.push_back(backRightUp[2]);

//    grani.push_back(faceLeftBottom[0]);
//    grani.push_back(faceLeftBottom[1]);
//    grani.push_back(faceLeftBottom[2]);
//    grani.push_back(faceRightBottom[0]);
//    grani.push_back(faceRightBottom[1]);
//    grani.push_back(faceRightBottom[2]);
//    grani.push_back(backRightBottom[0]);
//    grani.push_back(backRightBottom[1]);
//    grani.push_back(backRightBottom[2]);
//    grani.push_back(faceLeftBottom[0]);
//    grani.push_back(faceLeftBottom[1]);
//    grani.push_back(faceLeftBottom[2]);
//    grani.push_back(faceRightBottom[0]);
//    grani.push_back(faceRightBottom[1]);
//    grani.push_back(faceRightBottom[2]);
//    grani.push_back(backLeftBottom[0]);
//    grani.push_back(backLeftBottom[1]);
//    grani.push_back(backLeftBottom[2]);

//    grani.push_back(faceLeftUp[0]);
//    grani.push_back(faceLeftUp[1]);
//    grani.push_back(faceLeftUp[2]);
//    grani.push_back(faceRightUp[0]);
//    grani.push_back(faceRightUp[1]);
//    grani.push_back(faceRightUp[2]);
//    grani.push_back(backRightUp[0]);
//    grani.push_back(backRightUp[1]);
//    grani.push_back(backRightUp[2]);
//    grani.push_back(faceLeftUp[0]);
//    grani.push_back(faceLeftUp[1]);
//    grani.push_back(faceLeftUp[2]);
//    grani.push_back(faceRightUp[0]);
//    grani.push_back(faceRightUp[1]);
//    grani.push_back(faceRightUp[2]);
//    grani.push_back(backLeftUp[0]);
//    grani.push_back(backLeftUp[1]);
//    grani.push_back(backLeftUp[2]);

//    grani.push_back(faceRightBottom[0]);
//    grani.push_back(faceRightBottom[1]);
//    grani.push_back(faceRightBottom[2]);
//    grani.push_back(backRightUp[0]);
//    grani.push_back(backRightUp[1]);
//    grani.push_back(backRightUp[2]);
//    grani.push_back(backRightBottom[0]);
//    grani.push_back(backRightBottom[1]);
//    grani.push_back(backRightBottom[2]);
//    grani.push_back(faceRightBottom[0]);
//    grani.push_back(faceRightBottom[1]);
//    grani.push_back(faceRightBottom[2]);
//    grani.push_back(backRightUp[0]);
//    grani.push_back(backRightUp[1]);
//    grani.push_back(backRightUp[2]);
//    grani.push_back(faceRightUp[0]);
//    grani.push_back(faceRightUp[1]);
//    grani.push_back(faceRightUp[2]);

//    grani.push_back(faceLeftBottom[0]);
//    grani.push_back(faceLeftBottom[1]);
//    grani.push_back(faceLeftBottom[2]);
//    grani.push_back(backLeftUp[0]);
//    grani.push_back(backLeftUp[1]);
//    grani.push_back(backLeftUp[2]);
//    grani.push_back(backLeftBottom[0]);
//    grani.push_back(backLeftBottom[1]);
//    grani.push_back(backLeftBottom[2]);
//    grani.push_back(faceLeftBottom[0]);
//    grani.push_back(faceLeftBottom[1]);
//    grani.push_back(faceLeftBottom[2]);
//    grani.push_back(backLeftUp[0]);
//    grani.push_back(backLeftUp[1]);
//    grani.push_back(backLeftUp[2]);
//    grani.push_back(faceLeftUp[0]);
//    grani.push_back(faceLeftUp[1]);
//    grani.push_back(faceLeftUp[2]);
}

void smallCube::Init() {

    faceLeftBottom[0] = GetX()-0.09; faceLeftBottom[1] = GetY()-0.09, faceLeftBottom[2] = GetZ()-0.09;
    faceRightBottom[0] = GetX()+0.09, faceRightBottom[1] = GetY()-0.09, faceRightBottom[2] = GetZ()-0.09;
    faceRightUp[0] = GetX() + 0.09, faceRightUp[1] = GetY()+0.09, faceRightUp[2] = GetZ()-0.09;
    faceLeftUp[0] = GetX() - 0.09, faceLeftUp[1] = GetY()+0.09, faceLeftUp[2] = GetZ()-0.09;
    backLeftBottom[0] = GetX()-0.09, backLeftBottom[1] = GetY()-0.09, backLeftBottom[2] = GetZ()+0.09;
    backRightBottom[0] =  GetX()+0.09, backRightBottom[1] = GetY()-0.09, backRightBottom[2] = GetZ()+0.09;
    backLeftUp[0] = GetX()-0.09, backLeftUp[1] = GetY()+0.09, backLeftUp[2] = GetZ()+0.09;
    backRightUp[0] = GetX() + 0.09, backRightUp[1] = GetY()+0.09, backRightUp[2] = GetZ()+0.09;

}

float smallCube::GetX() {
    return X;
}
float smallCube::GetY() {
    return Y;
}

float smallCube::GetZ() {
    return Z;
}

void smallCube::SetX(float x) {
    X = x;
}

void smallCube::SetY(float y) {
    Y = y;
}

void smallCube::SetZ(float z) {
    Z = z;
}