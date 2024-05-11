//
// Created by Andrei Banakh on 04.04.2024.
//

#include "smallCube.h"

void smallCube::Draw(std::vector<Shader*>shaders, glm::mat4 MVP) {
    std::vector<float> grani;
    //front
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[3][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[0][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[1][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[3][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[1][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[2][i]);
    }
    //left
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[0][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[6][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[4][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[0][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[6][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[3][i]);
    }
    //back
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[6][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[4][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[5][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[6][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[5][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[7][i]);
    }
    //right
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[1][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[7][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[5][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[1][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[7][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[2][i]);
    }
    //bottom
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[0][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[1][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[5][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[0][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[4][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[5][i]);
    }
    //up
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[3][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[2][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[6][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[7][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[2][i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(vertices[6][i]);
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLfloat g_vertex_buffer_data[6*3*6];
    for (int gran = 0; gran < grani.size(); gran++) {
        g_vertex_buffer_data[gran] = grani[gran];
    }
    grani.clear();
    GLuint vertexbuffer;
    glGenBuffers(1,&vertexbuffer);                                                                                     // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);                                                                        // Сделаем только что созданный буфер текущим
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);                  // Передадим информацию о вершинах в OpenGL
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // Атрибут 0.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void *) 0            // Смещение массива в буфере
    );
    MVP = MVP * model;
    for (int i = 0; i < 6; i++) { //рисую по 6 граней с 6 разными цветами
        shaders[Side(i)]->use();
        GLint MatrixID = glGetUniformLocation(shaders[Side(i)]->id, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glDrawArrays(GL_TRIANGLES, i*6, 6);
    }
    glBufferSubData(vertexbuffer, 0, 3, (void*) 0);
    glDeleteVertexArrays(1, &VertexArrayID); //в идеале бы 1 раз создавать буфферы но я создаю их кучу раз и кучу раз очищаю
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &vertexbuffer);
    glDeleteBuffers(1, &VertexArrayID);
}

void smallCube::Init(float size) {
    const float a = 0.15f;
    //test 0.05 game (a * size)
    if (GetX() != size/3) {
        SetSide(3, 6);
    }
    if (GetX() != -size/3) {
        SetSide(1, 6);
    }
    if (GetY() != -size/3) {
        SetSide(4, 6);
    }
    if (GetY() != size/3) {
        SetSide(5, 6);
    }
    if (GetZ() != size/3) {
        SetSide(2, 6);
    }
    if (GetZ() != -size/3) {
        SetSide(0, 6);
    }
    vertices[0][0] = GetX() - (a * size); vertices[0][1] = GetY() - (a * size); vertices[0][2] = GetZ() - (a * size); // faceLeftBottom
    vertices[1][0] = GetX() + (a * size); vertices[1][1] = GetY() - (a * size); vertices[1][2] = GetZ() - (a * size); // faceRightBottom
    vertices[2][0] = GetX() + (a * size); vertices[2][1] = GetY() + (a * size); vertices[2][2] = GetZ() - (a * size); // faceRightUp
    vertices[3][0] = GetX() - (a * size); vertices[3][1] = GetY() + (a * size); vertices[3][2] = GetZ() - (a * size); // faceLeftUp
    vertices[4][0] = GetX() - (a * size); vertices[4][1] = GetY() - (a * size); vertices[4][2] = GetZ() + (a * size); // backLeftBottom
    vertices[5][0] = GetX() + (a * size); vertices[5][1] = GetY() - (a * size); vertices[5][2] = GetZ() + (a * size); // backRightBottom
    vertices[6][0] = GetX() - (a * size); vertices[6][1] = GetY() + (a * size); vertices[6][2] = GetZ() + (a * size); // backLeftUp
    vertices[7][0] = GetX() + (a * size); vertices[7][1] = GetY() + (a * size); vertices[7][2] = GetZ() + (a * size); // backRightUp
}

void smallCube::turnleft(){
    char newsides[6];
    for (int i = 1; i < 4; i++) {
        newsides[i] = sides[i-1];
    }
    newsides[0] = sides[3];
    newsides[4] = sides[4];
    newsides[5] = sides[5];
    for (int i = 0; i < 6; i++) {
        sides[i] = newsides[i];
    }
}
void smallCube::turnright(){
    char newsides[6];
    for (int i = 0; i < 3; i++) {
        newsides[i] = sides[i+1];
    }
    newsides[3] = sides[0];
    newsides[4] = sides[4];
    newsides[5] = sides[5];
    for (int i = 0; i < 6; i++) {
        sides[i] = newsides[i];
    }
}
void smallCube::turnup(){
    char newsides[6];
    newsides[0] = sides[5];
    newsides[5] = sides[2];
    newsides[2] = sides[4];
    newsides[1] = sides[1];
    newsides[3] = sides[3];
    newsides[4] = sides[0];
    for (int i = 0; i < 6; i++) {
        sides[i] = newsides[i];
    }
}
void smallCube::turndown(){
    char newsides[6];
    newsides[0] = sides[4];
    newsides[1] = sides[1];
    newsides[2] = sides[5];
    newsides[3] = sides[3];
    newsides[4] = sides[2];
    newsides[5] = sides[0];
    for (int i = 0; i < 6; i++) {
        sides[i] = newsides[i];
    }
}

float smallCube::GetX() {
    return xyz.x;
}
float smallCube::GetY() {
    return xyz.y;
}

float smallCube::GetZ() {
    return xyz.z;
}

void smallCube::SetX(float x) {
    xyz.x = x;
}

void smallCube::SetY(float y) {
    xyz.y = y;
}

void smallCube::SetZ(float z) {
    xyz.z = z;
}

char smallCube::Side(int id) {
    return sides[id];
}

void smallCube::SetSide(int index, int id) {
    sides[index] = id;
}
