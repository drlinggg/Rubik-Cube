//
// Created by Andrei Banakh on 04.04.2024.
//

#include "cubeDLG.h"
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
            shuffle();
        }
    }
    //test
    if (glfwGetKey(window, GLFW_KEY_1)) {
        reCalc();
        angleHor+=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_2)) {
        reCalc();
        angleVer+=0.01;
    }

    if (glfwGetKey(window, GLFW_KEY_EQUAL)) {
        reCalc();
        radius+=0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS)) {
        reCalc();
        radius-=0.01;
    }ка
    if (glfwGetKey(window, GLFW_KEY_A)) {
        if (!glfwGetKey(window, GLFW_KEY_A)) {
            br.turnVer(0, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S)) {
        if (!glfwGetKey(window, GLFW_KEY_S)) {
            br.turnVer(1, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        if (!glfwGetKey(window, GLFW_KEY_D)) {
            br.turnVer(2, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_Q)) {
        if (!glfwGetKey(window, GLFW_KEY_Q)) {
            br.turnVer(0, 1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W)) {
        if (!glfwGetKey(window, GLFW_KEY_W)) {
            br.turnVer(1, 1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_E)) {
        if (!glfwGetKey(window, GLFW_KEY_E)) {
            br.turnVer(2, 1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_R)) {
        if (!glfwGetKey(window, GLFW_KEY_R)) {
            br.turnHor(0, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_T)) {
        if (!glfwGetKey(window, GLFW_KEY_T)) {
            br.turnHor(1, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_Y)) {
        if (!glfwGetKey(window, GLFW_KEY_Y)) {
            br.turnHor(2, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_F)) {
        if (!glfwGetKey(window, GLFW_KEY_F)) {
            br.turnHor(0, 1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_G)) {
        if (!glfwGetKey(window, GLFW_KEY_G)) {
            br.turnHor(1, 1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_H)) {
        if (!glfwGetKey(window, GLFW_KEY_H)) {
            br.turnHor(2, 1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_U)) {
        if (!glfwGetKey(window, GLFW_KEY_U)) {
            br.turnThrough(2, -1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_J)) {
        if (!glfwGetKey(window, GLFW_KEY_J)) {
            br.turnThrough(2, 1);
        }
    }
}

void CubeDlg::shuffle() {
    int countOperations = rand() % 1000;
    //FILE* save = fopen("../input.txt", "w");
    char way, id, mode;
    for (int i = 0; i < countOperations; i++) {
        way = rand()%3;
        id = rand()%3;
        mode = rand()%2-1;
        if (way == 0) {
            br.turnHor(id, mode);
        }
        else if (way == 1){
            br.turnVer(id, mode);
        }
        else {
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

