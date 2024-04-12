//
// Created by Andrei Banakh on 04.04.2024.
//

#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifndef LRCUBE_SMALLCUBE_H
#define LRCUBE_SMALLCUBE_H

class smallCube{                               //кубик 1x1
private:
    float X;
    float Y;
    float Z;
    char sides[6] = {0,1,2,3,4,5}; //front left back right bottom up
    float faceLeftBottom[3];
    float faceRightBottom[3];
    float faceLeftUp[3];
    float faceRightUp[3];
    float backLeftBottom[3];
    float backRightBottom[3];
    float backLeftUp[3];
    float backRightUp[3];
public:
    glm::mat4 model = glm::mat4(1.0f);
    char Side(int id);
    void SetSide(int index, int id);
    void Draw(std::vector<Shader*> shaders, glm::mat4 MVP);
    void Init(float size);
    float GetX();
    float GetY();
    float GetZ();
    void SetX(float x);
    void SetY(float y);
    void SetZ(float z);
    void turnleft(); // 0->1 1->2 2->3 3->0
    void turnright(); // 0->3 1->0 2->1 3->2
    void turnup(); // 0->5 5->2 2->4 4->0
    void turndown(); // 0->4 4->2 2->5 5->0
};

#endif //LRCUBE_SMALLCUBE_H