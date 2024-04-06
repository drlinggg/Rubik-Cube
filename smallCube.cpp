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

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    GLfloat g_vertex_buffer_data[grani.size()];
    for (int gran = 0; gran < grani.size(); gran++) {
        g_vertex_buffer_data[gran] = grani[gran];
    }
    GLuint vertexbuffer;// Это будет идентификатором нашего буфера вершин
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
    for (int i = 0; i < 6; i++) {
        GLuint MatrixID = glGetUniformLocation(shaders[sides[i]]->id, "MVP");
        // Передать наши трансформации в текущий шейдер
        // Это делается в основном цикле, поскольку каждая модель будет иметь другую MVP-матрицу (как минимум часть M)
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        shaders[sides[i]]->use();
        glDrawArrays(GL_TRIANGLES, i*6, 6);
    }
}

void smallCube::Init() {

    //test 0.05 game 0.09
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