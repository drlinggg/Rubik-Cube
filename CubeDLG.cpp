//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cubeDLG.h"
#include "Windows.h"
using namespace glm;

int CubeDlg::init() {
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
    glEnable(GL_DEPTH_TEST);
    shaders.resize(6); //грузим шейдеры сторон
    shaders[0] = load_shader("../main.glslv", "../main.glslf");
    shaders[1] = load_shader("../main.glslv", "../left.glslf");
    shaders[2] = load_shader("../main.glslv", "../back.glslf");
    shaders[3] = load_shader("../main.glslv", "../right.glslf");
    shaders[4] = load_shader("../main.glslv", "../bottom.glslf");
    shaders[5] = load_shader("../main.glslv", "../up.glslf");
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    angleHor = 0;
    angleVer = 0;
    return 0;
}

void CubeDlg::drawScene() {
    glLoadIdentity();
    glFinish();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //получаем матрицу для преображения точек относительно камеры
    glm::mat4 Projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
    glm::mat4 View = glm::lookAt(
            glm::vec3(x,y,z), // Камера находится в мировых координатах (4,3,3)
            glm::vec3(0,0,0), // И направлена в начало координат
            glm::vec3(0,1,0)  // "Голова" находится сверху
    );
    glm::mat4 Model = glm::mat4(1.0f);  // Индивидуально для каждой модели
    glm::mat4 MVP = Projection * View * Model;
    //рисуем куб с помощью шейдеров и матрицы
    br.Draw(shaders, MVP);
    glfwSwapBuffers(window);
}

void CubeDlg::reCalc() {
    glm::vec3 direction;
    direction.x = radius * sin(angleHor);
    direction.y = radius * cos(angleVer);
    direction.z = radius * cos(angleHor);
    glm::normalize(direction);
    x = direction[0];
    y = direction[1];
    z = direction[2];
}

void CubeDlg::processInput() {
    if (glfwGetKey(window, GLFW_KEY_9)) {
        if (!glfwGetKey(window, GLFW_KEY_9)) {
            shuffle(30);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_0)) {
        if (!glfwGetKey(window, GLFW_KEY_0)) {
            solve(0);
        }
    }

    if (glfwGetKey(window, GLFW_KEY_G)) {
        if (!glfwGetKey(window, GLFW_KEY_G)) {
            br.turnHor(0,-1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_H)) {
        if (!glfwGetKey(window, GLFW_KEY_H)) {
            br.turnVer(1,1);
        }
    }


    if (glfwGetKey(window, GLFW_KEY_W)) {
        reCalc();
        if (angleVer < 0) {
            angleVer += 0.01;
        }
        std::cout << angleVer << '\n';
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        reCalc();
        if (angleVer > -2.99) {
            angleVer -= 0.01;
        }
        std::cout << angleVer << '\n';
    }

    if (glfwGetKey(window, GLFW_KEY_A)) {
        reCalc();
        angleHor-=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        reCalc();
        angleHor+=0.01;
    }

}

void CubeDlg::shuffle(int countOperations) {
    //FILE* save = fopen("../input.txt", "w");
    char way, id, mode;
    for (int i = 0; i < countOperations; i++) {
        way = rand()%3;
        id = rand()%3;
        mode = rand()%2-1;
        if (way == 0 && id != 1) {
            br.turnHor(id, mode);
        }
        else if (way == 1 && id != 1){
            br.turnVer(id, mode);
        }
        else if (way == 2 && id != 1) {
            br.turnThrough(id, mode);
        }
        drawScene();
        //std::putc(way+97,save);
        //std::putc(id+97,save);
        //std::putc(mode+98,save);
    }
    //std::fclose(save);
}


GLFWwindow* CubeDlg::getWindow() {
    return window;
}

void CubeDlg::solve(int miliSeconds) {
    assembling_cross(miliSeconds);//Сборка неправильного креста
    F2L(miliSeconds);
    OLL(miliSeconds);
    PLL(miliSeconds);
}

void CubeDlg::assembling_cross(int miliSeconds) { //front left back right bottom up
    for (int k = 0; k < 100; k++) {
        if (br.bricks[1][2][0].Side(0) != 0 && br.bricks[1][2][0].Side(5) == 5 ||
            br.bricks[0][2][1].Side(1) != 1 && br.bricks[0][2][1].Side(5) == 5 ||
            br.bricks[1][2][2].Side(2) != 2 && br.bricks[1][2][2].Side(5) == 5 ||
            br.bricks[2][2][1].Side(3) != 3 && br.bricks[2][2][1].Side(5) == 5) {
            while (true) {
                br.turnHor(2, -1);
                if (br.bricks[1][2][0].Side(0) == 0 && br.bricks[1][2][0].Side(5) == 5 ||
                    br.bricks[0][2][1].Side(1) == 1 && br.bricks[0][2][1].Side(5) == 5 ||
                    br.bricks[1][2][2].Side(2) == 2 && br.bricks[1][2][2].Side(5) == 5 ||
                    br.bricks[2][2][1].Side(3) == 3 && br.bricks[2][2][1].Side(5) == 5) {
                    break;
                }
            }
        }
        //    frontSide;
        if (br.bricks[0][1][0].Side(0) == 5) {
            if (br.bricks[0][2][1].Side(5) == 5) {
                br.turnHor(2, -1);
                br.turnVer(0, -1);
                br.turnHor(2, 1);
            }
            else {
                br.turnVer(0, -1);
            }
        }
        ;

        if (br.bricks[2][1][0].Side(0) == 5) {
            if (br.bricks[2][2][1].Side(5) == 5) {
                br.turnHor(2, 1);
                br.turnVer(2, -1);
                br.turnHor(2, -1);
            }
            else {
                br.turnVer(2, -1);
            }
        }
        ;
        if (br.bricks[1][2][0].Side(0) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                br.turnThrough(0, 1);
                br.turnVer(2, -1);
            }
            else {
                br.turnThrough(0, -1);
                br.turnVer(0, -1);
            }
        }
        ;
        if (br.bricks[1][0][0].Side(0) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                br.turnThrough(0, 1);
                br.turnVer(0, -1);
            }
            else {
                br.turnThrough(0, -1);
                br.turnVer(2, -1);
            }
        }
        ;
        //backSide;
        if (br.bricks[0][1][2].Side(2) == 5) {
            if (br.bricks[0][2][1].Side(5) == 5) {
                br.turnHor(2, -1);
                br.turnVer(0, 1);
                br.turnHor(2, 1);
            }
            else {
                br.turnVer(0, 1);
            }
        }
        ;
        if (br.bricks[2][1][2].Side(2) == 5) {
            if (br.bricks[2][2][1].Side(5) == 5) {
                br.turnHor(2, -1);
                br.turnVer(2, 1);
                br.turnHor(2, 1);
            }
            else {
                br.turnVer(2, 1);
            }
        }
        ;
        if (br.bricks[1][2][2].Side(2) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                br.turnThrough(2, -1);
                br.turnVer(0, 1);
            }
            else {
                br.turnThrough(2, 1);
                br.turnVer(2, 1);
            }
        }
        ;
        if (br.bricks[1][0][2].Side(2) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                br.turnThrough(2, -1);
                br.turnVer(0, 1);
            }
            else {
                br.turnThrough(2, 1);
                br.turnVer(2, 1);
            }
        }
        ;
//        left  нижний слой ошибка
        if (br.bricks[0][1][0].Side(1) == 5) {
            if (br.bricks[1][2][0].Side(5) == 5) {
                br.turnHor(2, -1);
                br.turnThrough(0, 1);
                br.turnHor(2, 1);
            }
            else {
                br.turnThrough(0, 1);
            }
        }
        ;
        if (br.bricks[0][1][2].Side(1) == 5) {
            if (br.bricks[1][2][2].Side(5) == 5) {
                br.turnHor(2, 1);
                br.turnThrough(2, 1);
                br.turnHor(2, -1);
            }
            else {
                br.turnThrough(2, 1);
            }
        }
        ;
        if (br.bricks[0][2][1].Side(1) == 5) {
            if (br.bricks[1][2][2].Side(5) == 5) {
                br.turnVer(0, 1);
                br.turnThrough(2, 1);
            }
            else {
                br.turnVer(0, -1);
                br.turnThrough(0, 1);
            }
        }
        ;
        if (br.bricks[0][1][0].Side(1) == 5) {
            if (br.bricks[1][2][0].Side(5) != 5) {
                br.turnVer(0, -1);
                br.turnThrough(0,1);
            }
            else if (br.bricks[1][2][2].Side(5) != 5){
                br.turnVer(0,1);
                br.turnThrough(2, 1);
            }
            else {
                br.turnHor(0,1);

            }
        }
        ;
        //right
        if (br.bricks[2][1][0].Side(3) == 5) {
            if (br.bricks[1][2][0].Side(5) == 5) {
                br.turnHor(2, -1);
                br.turnThrough(0, 1);
                br.turnHor(2, 1);
            }
            else{
                br.turnThrough(0, -1);
            }
        }
        ;
        if (br.bricks[2][1][2].Side(3) == 5) {
            if (br.bricks[1][2][2].Side(5) == 5) {
                br.turnHor(2, 1);
                br.turnThrough(2, 1);
                br.turnHor(2, -1);
            }
            else {
                br.turnThrough(2, 1);
            }
        }
        ;
        if (br.bricks[2][2][1].Side(3) == 5) {
            if (br.bricks[1][2][2].Side(5) == 5) {
                br.turnVer(0,1);
                br.turnThrough(0,-1);
            }
            else {
                br.turnVer(0, -1);
                br.turnThrough(2, -1);
            }
        }
        ;
        if (br.bricks[2][0][1].Side(3) == 5) {
            if (br.bricks[1][2][0].Side(5) != 5) {
                br.turnVer(0, -1);
                br.turnThrough(0,-1);
            }
            else if (br.bricks[1][2][2].Side(5) != 5){
                br.turnVer(0,1);
                br.turnThrough(2, -1);
            }
            else {
                br.turnHor(0,1);

            }
        }
        ;
        if (br.bricks[1][0][0].Side(4) == 5) {
            if (br.bricks[1][2][0].Side(5) != 5) {
                br.turnThrough(0, 1);
                br.turnThrough(0, 1);
            }
            else {
                br.turnThrough(0,1);
                br.turnHor(1,1);
            }
        }
        ;
        if (br.bricks[0][0][1].Side(4) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                br.turnVer(0, 1);
                br.turnVer(0, 1);
            }
            else {
                br.turnVer(0, 1);
                br.turnHor(1,1);
            }
        }
        ;
        if (br.bricks[1][0][2].Side(4) == 5) {
            if (br.bricks[1][2][2].Side(5) != 5) {
                br.turnThrough(2, 1);
                br.turnThrough(2, 1);
            }
            else {
                br.turnVer(0, 1);
                br.turnHor(1,1);
            }
        }
        ;
        if (br.bricks[2][0][1].Side(4) == 5) {
            if (br.bricks[2][2][1].Side(5) != 5){
                br.turnVer(2,1);
                br.turnVer(2,1);
            }
            else {
                br.turnVer(2,1);
                br.turnHor(1,1);
            }
        }
        br.turnHor(0,-1);
        Sleep(miliSeconds);
        drawScene();
    }
    //
    if (check_nn_cross()) {
        for (int k = 0; k < 16; k++) { //front left back right bottom up
            if (br.bricks[2][2][1].Side(3) == 2) {
                br.turnVer(2, 1);
                br.turnHor(2, -1);
                br.turnVer(2, -1);
                br.turnHor(2, 1);
            }
            else if (br.bricks[2][2][1].Side(3) == 1) {
                br.turnVer(2, -1);
                br.turnHor(2, -1);
                br.turnHor(2, -1);
                br.turnVer(2, 1);
                br.turnHor(2, -1);
                br.turnHor(2, -1);
                br.turnVer(2, -1);
            }
            else if (br.bricks[2][2][1].Side(3) == 0) {
                br.turnThrough(0, 1);
                br.turnVer(2, -1);
                br.turnThrough(0, -1);
                br.turnVer(2, 1);
            }
            if (br.bricks[1][2][0].Side(0) == 3 || br.bricks[2][2][1].Side(3) == 0) {
                br.turnThrough(0, 1);
                br.turnVer(2, -1);
                br.turnThrough(0, -1);
                br.turnVer(2, 1);
            }
            if (br.bricks[1][2][0].Side(0) != 0 || br.bricks[0][2][1].Side(1) != 1) {
                br.turnVer(0, 1);
                br.turnThrough(0, 1);
                br.turnVer(0, -1);
                br.turnThrough(0, -1);
            }
            if (br.bricks[1][2][0].Side(0) != 0 || br.bricks[1][2][2].Side(2) != 2) {
                br.turnThrough(0, 1);
                br.turnHor(2, -1);
                br.turnHor(2, -1);
                br.turnThrough(0, -1);
                br.turnHor(2, -1);
                br.turnHor(2, -1);
                br.turnThrough(0, 1);
            }
            if (br.bricks[0][2][1].Side(1) == 2 || br.bricks[1][2][2].Side(2) == 1) {
                br.turnThrough(2,-1);
                br.turnVer(0,1);
                br.turnThrough(2,1);
                br.turnVer(0,-1);
            }
            if (check_cross()) {
                return;
            }
        }
    }
}


void CubeDlg::F2L(int miliSeconds) {

}

void CubeDlg::OLL(int miliSeconds) {

}

void CubeDlg::PLL(int miliSeconds) {

}


bool CubeDlg::check_nn_cross() {
    int check = 0;
    (br.bricks[0][2][1].Side(5) == 5 ? check++ : NULL);
    (br.bricks[1][2][0].Side(5) == 5 ? check++ : NULL);
    (br.bricks[1][2][2].Side(5) == 5 ? check++ : NULL);
    (br.bricks[2][2][1].Side(5) == 5 ? check++ : NULL);
    if (check == 4) {
        return true;
    }
    return false;
}

bool CubeDlg::check_cross() {
    int check = 0;
    (br.bricks[0][2][1].Side(5) == 5 ? check++ : NULL);
    (br.bricks[1][2][0].Side(5) == 5 ? check++ : NULL);
    (br.bricks[1][2][2].Side(5) == 5 ? check++ : NULL);
    (br.bricks[2][2][1].Side(5) == 5 ? check++ : NULL);
    (br.bricks[0][2][1].Side(1) == 1 ? check++ : NULL);
    (br.bricks[1][2][0].Side(0) == 0 ? check++ : NULL);
    (br.bricks[1][2][2].Side(2) == 2 ? check++ : NULL);
    (br.bricks[2][2][1].Side(3) == 3 ? check++ : NULL);
    if (check == 8) {
        return true;
    }
    return false;
}