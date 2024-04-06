//
// Created by Andrei Banakh on 04.04.2024.
//

#include "smallCube.h"

void smallCube::Draw(std::vector<Shader*>shaders, glm::mat4 MVP) {
    std::vector<float> grani;
    //front
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
    //left
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftUp[i]);
    }
    //back
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightUp[i]);
    }
    //right
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightUp[i]);
    }
    //bottom
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftBottom[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightBottom[i]);
    }
    //up
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backRightUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(faceRightUp[i]);
    }
    for (int i = 0; i < 3; i++) {
        grani.push_back(backLeftUp[i]);
    }

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLfloat g_vertex_buffer_data[grani.size()];
    for (int gran = 0; gran < grani.size(); gran++) {
        g_vertex_buffer_data[gran] = grani[gran];
    }
    grani.clear();
    GLuint vertexbuffer;
    glGenBuffers(1,&vertexbuffer);                                                                                     // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
    glBindBuffer(GL_ARRAY_BUFFER,vertexbuffer);                                                                        // Сделаем только что созданный буфер текущим
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data,GL_STATIC_DRAW);                  // Передадим информацию о вершинах в OpenGL
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
            3,                  // Размер
            GL_FLOAT,           // Тип
            GL_FALSE,           // Указывает, что значения не нормализованы
            0,                  // Шаг
            (void *) 0            // Смещение массива в буфере
    );
    for (int i = 0; i < 6; i++) { //рисую по 6 граней с 6 разными цветами
        GLuint MatrixID = glGetUniformLocation(shaders[sides[i]]->id, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        shaders[sides[i]]->use();
        glDrawArrays(GL_TRIANGLES, i*6, 6);
    }
    glDeleteVertexArrays(1, &VertexArrayID); //в идеале бы 1 раз создавать буфферы но я создаю их кучу раз и кучу раз очищаю
    glDeleteBuffers(1, &vertexbuffer);
}

void smallCube::Init() {

    //test 0.05 game 0.09
    faceLeftBottom[0] = GetX()-0.09; faceLeftBottom[1] = GetY()-0.09, faceLeftBottom[2] = GetZ()-0.09; //прорезы между кубами
    faceRightBottom[0] = GetX()+0.09, faceRightBottom[1] = GetY()-0.09, faceRightBottom[2] = GetZ()-0.09;
    faceRightUp[0] = GetX() + 0.09, faceRightUp[1] = GetY()+0.09, faceRightUp[2] = GetZ()-0.09;
    faceLeftUp[0] = GetX() - 0.09, faceLeftUp[1] = GetY()+0.09, faceLeftUp[2] = GetZ()-0.09;
    backLeftBottom[0] = GetX()-0.09, backLeftBottom[1] = GetY()-0.09, backLeftBottom[2] = GetZ()+0.09;
    backRightBottom[0] =  GetX()+0.09, backRightBottom[1] = GetY()-0.09, backRightBottom[2] = GetZ()+0.09;
    backLeftUp[0] = GetX()-0.09, backLeftUp[1] = GetY()+0.09, backLeftUp[2] = GetZ()+0.09;
    backRightUp[0] = GetX() + 0.09, backRightUp[1] = GetY()+0.09, backRightUp[2] = GetZ()+0.09;

}

void smallCube::turnleft(){ // 0->1 1->2 2->3 3->0
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
void smallCube::turnright(){ // 0->3 3->2 1->0 2->1
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
void smallCube::turnup(){ // 0->5 5->2 2->4 4->0
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
void smallCube::turndown(){ // 0->4 4->2 2->5 5->0 //front left back right bottom up
    char newsides[6];
    newsides[0] = sides[5];
    newsides[1] = sides[1];
    newsides[2] = sides[4];
    newsides[3] = sides[3];
    newsides[4] = sides[0];
    newsides[5] = sides[2];
    for (int i = 0; i < 6; i++) {
        sides[i] = newsides[i];
    }
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