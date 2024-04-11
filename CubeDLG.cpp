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
            glm::vec3(x,y,z), // Камера находится в мировых координатах
            glm::vec3(0,0,0), // И направлена в начало координат
            glm::vec3(0,1,0)  // "Голова" находится сверху
    );
    glm::mat4 Model = glm::mat4(1.0f);  // Индивидуально для каждой модели
    Model = glm::rotate(Model, radians(0.0f), glm::vec3(1, 1, 1)); // where x, y, z is axis of rotation (e.g. 0 1 0)
    glm::mat4 MVP = Projection * View * Model;

    //рисуем куб с помощью шейдеров и матрицы
    br.Draw(shaders, MVP);
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
            shuffle(30);
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_0)) {
        if (!glfwGetKey(window, GLFW_KEY_0)) {
            solve();
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
        std::cout << angleHor << '\n';
    }
    if (glfwGetKey(window, GLFW_KEY_D)) {
        reCalc();
        angleHor+=0.01;
        std::cout << angleHor << '\n';
    }
    if (glfwGetKey(window, GLFW_KEY_F)) {
        if (!glfwGetKey(window, GLFW_KEY_F)) {
            turnHor(2,1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_V)) {
        if (!glfwGetKey(window, GLFW_KEY_V)) {
            turnHor(1,-1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B)) {
        if (!glfwGetKey(window, GLFW_KEY_B)) {
            turnVer(2,1);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_N)) {
        if (!glfwGetKey(window, GLFW_KEY_N)) {
            turnThrough(1,1);
        }
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
        //std::putc(way+97,save);
        //std::putc(id+97,save);
        //std::putc(mode+98,save);
    }
    //std::fclose(save);
}


GLFWwindow* CubeDlg::getWindow() {
    return window;
}

void CubeDlg::solve() {
    assembling_cross();//Сборка неправильного креста
    for (int i = 0; i < 2; i++) {
        turnVer(0,1);
        turnVer(1,1);
        turnVer(2,1);
    }
    Sleep(1000);
    FF();
    Sleep(1000);
    SF();
    Sleep(1000);
    CRUP();
    Sleep(1000);
    for (int i = 0; i < 3; i++) {
        turnThrough(i,-1);
    }
    Sleep(1000);
    CRUP2();
    Sleep(1000);
    for (int i = 0; i < 3; i++) {
        turnThrough(i,1);
    }
    vertexlvl3();
    Sleep(1000);
    edgelvl3();
}

void CubeDlg::assembling_cross() { //front left back right bottom up
    while (!check_nn_cross()) {
        //    frontSide;
        if (br.bricks[1][0][0].Side(4) == 5) {
            turnThrough(0,-1);
        }
        if (br.bricks[0][1][0].Side(0) == 5) {
            if (br.bricks[0][2][1].Side(5) == 5) {
                turnHor(2, -1);
                turnVer(0, -1);
                turnHor(2, 1);
            } else {
                turnVer(0, -1);
            }
        };
        if (br.bricks[2][1][0].Side(0) == 5) {
            if (br.bricks[2][2][1].Side(5) == 5) {
                turnHor(2, 1);
                turnVer(2, -1);
                turnHor(2, -1);
            } else {
                turnVer(2, -1);
            }
        };
        if (br.bricks[1][2][0].Side(0) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                turnThrough(0, 1);
                turnVer(2, -1);
            } else {
                turnThrough(0, -1);
                turnVer(0, -1);
            }
        };
        if (br.bricks[1][0][0].Side(0) == 5) {
            if (br.bricks[0][2][1].Side(5) != 5) {
                turnThrough(0, 1);
                turnVer(0, -1);
            } else {
                turnThrough(0, -1);
                turnVer(2, -1);
            }
        }
        turnHor(0,1);
        turnHor(1,1);
        turnHor(2,1);
    }
    std::cout << "nn solved\n";
    while (!check_cross()) {
        //front left back right bottom up
        if (br.bricks[2][2][1].Side(3) == br.bricks[1][1][2].Side(2) && br.bricks[1][2][2].Side(2) == br.bricks[2][1][1].Side(3)) {
            pifpaf1();
            turnVer(2, -1);
        }
        else if (br.bricks[0][2][1].Side(1) == br.bricks[2][1][1].Side(3) || br.bricks[2][2][1].Side(3) == br.bricks[0][1][1].Side(1)) {
            pifpaf2();
        }
        turnHor(0,-1);
        turnHor(1,-1);
        turnHor(2,-1);
    }
    std::cout << "cross solved\n";
}


bool CubeDlg::check_nn_cross() {
    int check = 0;
    (br.bricks[0][2][1].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[1][2][0].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[1][2][2].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[2][2][1].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    if (check == 4) {
        return true;
    }
    return false;
}

bool CubeDlg::check_cross() {
    int check = 0;
    (br.bricks[0][2][1].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[1][2][0].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[1][2][2].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[2][2][1].Side(5) == br.bricks[1][2][1].Side(5) ? check++ : NULL);
    (br.bricks[0][2][1].Side(1) == br.bricks[0][1][1].Side(1) ? check++ : NULL);
    (br.bricks[1][2][0].Side(0) == br.bricks[1][1][0].Side(0) ? check++ : NULL);
    (br.bricks[1][2][2].Side(2) == br.bricks[1][1][2].Side(2) ? check++ : NULL);
    (br.bricks[2][2][1].Side(3) == br.bricks[2][1][1].Side(3) ? check++ : NULL);
    if (check == 8) {
        return true;
    }
    return false;
}

void CubeDlg::turnHor(int hor, int mode) {
    float totalAngle = 0;
    while (85.0f >= totalAngle) {
        totalAngle += 5;
        glLoadIdentity();
        glFinish();
        glm::mat4 Projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 View = glm::lookAt(
                glm::vec3(x,y,z), // Камера находится в мировых координатах
                glm::vec3(0,0,0), // И направлена в начало координат
                glm::vec3(0,1,0)  // "Голова" находится сверху
        );
        glm::mat4 Model = glm::mat4(1.0f);// Индивидуально для каждой модели
        Model = glm::rotate(Model, radians(totalAngle), glm::vec3(0, -1 * mode, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
        glm::mat4 MVP = Projection * View;
        glm::mat4 MVProt = Projection * View * Model;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    if (y == hor) {
                        br.bricks[x][hor][z].Draw(shaders, MVProt);
                    }
                    br.bricks[x][y][z].Draw(shaders, MVP);
                }
            }
        }
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    br.turnHor(hor, mode);
    drawScene();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sleep(300);
}

void CubeDlg::turnVer(int ver, int mode) {
    float totalAngle = 0;
    while (90.0f >= totalAngle) {
        totalAngle += 5;
        glLoadIdentity();
        glFinish();
        glm::mat4 Projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 View = glm::lookAt(
                glm::vec3(x,y,z), // Камера находится в мировых координатах
                glm::vec3(0,0,0), // И направлена в начало координат
                glm::vec3(0,1,0)  // "Голова" находится сверху
        );
        glm::mat4 Model = glm::mat4(1.0f);// Индивидуально для каждой модели
        Model = glm::rotate(Model, radians(totalAngle), glm::vec3(-1 * mode, 0, 0)); // where x, y, z is axis of rotation (e.g. 0 1 0)
        glm::mat4 MVP = Projection * View;
        glm::mat4 MVProt = Projection * View * Model;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    if (x == ver) {
                        br.bricks[ver][y][z].Draw(shaders,MVProt);
                    }
                    br.bricks[x][y][z].Draw(shaders, MVP);
                }
            }
        }
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    br.turnVer(ver, mode);
    drawScene();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sleep(300);
}

void CubeDlg::turnThrough(int ver, int mode) {
    float totalAngle = 0;
    while (90.0f >= totalAngle) {
        totalAngle += 5;
        glLoadIdentity();
        glFinish();
        glm::mat4 Projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);
        glm::mat4 View = glm::lookAt(
                glm::vec3(x,y,z), // Камера находится в мировых координатах
                glm::vec3(0,0,0), // И направлена в начало координат
                glm::vec3(0,1,0)  // "Голова" находится сверху
        );
        glm::mat4 Model = glm::mat4(1.0f);// Индивидуально для каждой модели
        Model = glm::rotate(Model, radians(totalAngle), glm::vec3(0, 0, -1 * mode)); // where x, y, z is axis of rotation (e.g. 0 1 0)
        glm::mat4 MVP = Projection * View;
        glm::mat4 MVProt = Projection * View * Model;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                for (int z = 0; z < 3; z++) {
                    if (z == ver) {
                        br.bricks[x][y][ver].Draw(shaders,MVProt);
                    }
                    br.bricks[x][y][z].Draw(shaders, MVP);
                }
            }
        }
        glfwSwapBuffers(window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    br.turnThrough(ver, mode);
    drawScene();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Sleep(300);
}

void CubeDlg::pifpaf1() {
    turnVer(2, -1);
    turnHor(2, -1);
    turnVer(2, 1);
    turnHor(2, 1);
}

void CubeDlg::leftpifpaf() {
    turnVer(0,-1);
    turnHor(2,1);
    turnVer(0,1);
    turnHor(2,-1);
}

void CubeDlg::pifpaf2() {
    turnVer(2, 1);
    turnHor(2, -1);
    turnHor(2, -1);
    turnVer(2, -1);
    turnHor(2, -1);
    turnHor(2, -1);
    turnVer(2, 1);
}

void CubeDlg::FF() {
    while (!check_level1()) {
        for (int k = 0; k < 11; k++) {//front left back right bottom up
            if (br.bricks[2][2][0].Side(0) == br.bricks[1][0][1].Side(4) &&
                br.bricks[2][2][0].Side(5) == br.bricks[1][1][0].Side(0) &&
                br.bricks[2][2][0].Side(3) == br.bricks[2][1][1].Side(3)) {
                for (int i = 0; i < 5; i++) {
                    pifpaf1();
                }
            } else if (br.bricks[2][2][0].Side(0) == br.bricks[1][1][0].Side(0) &&
                       br.bricks[2][2][0].Side(5) == br.bricks[2][1][1].Side(3) &&
                       br.bricks[2][2][0].Side(3) == br.bricks[1][0][1].Side(4)) {
                pifpaf1();
            } else if (br.bricks[2][2][0].Side(0) == br.bricks[2][1][1].Side(3) &&
                       br.bricks[2][2][0].Side(5) == br.bricks[1][0][1].Side(4) &&
                       br.bricks[2][2][0].Side(3) == br.bricks[1][1][0].Side(0)) {
                for (int i = 0; i < 3; i++) {
                    pifpaf1();
                }
            } else if (br.bricks[2][0][0].Side(0) != br.bricks[1][1][0].Side(0) ||
                       br.bricks[2][0][0].Side(3) != br.bricks[2][1][1].Side(3) ||
                       br.bricks[2][0][0].Side(4) != br.bricks[1][0][1].Side(4)) {
                pifpaf1();
            }
            if (k <= 5) {
                turnHor(2,-1);
            }
            else {
                turnHor(2,-1);
                turnHor(1,-1);
                turnHor(0,-1);
            }
        }
    }
    std::cout << "1lvl solved\n";
    //todo fix all different 80% workin rn fix1step too
    while (br.bricks[1][1][0].Side(0) != 0) {
        turnHor(0,-1);
        turnHor(1,-1);
        turnHor(2,-1);
    }
}

void CubeDlg::SF() {
    while (!check_level2()) {
        for (int k = 0; k < 11; k++) {
            if (br.bricks[1][2][0].Side(0) == br.bricks[1][1][0].Side(0)
                && br.bricks[1][2][0].Side(5) == br.bricks[0][1][1].Side(1)) {
                turnHor(2, 1);
                leftpifpaf();
                turnHor(2, 1);
                turnHor(1, 1);
                turnHor(0, 1);
                pifpaf1();
            } else if (br.bricks[1][2][0].Side(0) == br.bricks[1][1][0].Side(0)
                       && br.bricks[1][2][0].Side(5) == br.bricks[2][1][1].Side(3)) {
                turnHor(2, -1);
                pifpaf1();
                turnHor(2, -1);
                turnHor(1, -1);
                turnHor(0, -1);
                leftpifpaf();
            } else if (br.bricks[2][1][0].Side(3) != br.bricks[2][1][1].Side(3)
                    && br.bricks[2][1][0].Side(0) != br.bricks[1][1][0].Side(0)) {
                pifpaf1();
                turnHor(2, -1);
                turnHor(1, -1);
                turnHor(0, -1);
                leftpifpaf();
            }
            if (k <= 5) {
                turnHor(2, -1);
            }
            else {
                turnHor(0,-1);
                turnHor(1,-1);
                turnHor(2,-1);
            }
        }
    }
    std::cout << "2lvl solved\n";
}

void CubeDlg::CRUP() {
    for (int k = 0; k < 16; k++) {
        Sleep(1000);
        //front left back right bottom up
        //wrong!!
        if (br.bricks[0][2][1].Side(4) == br.bricks[1][2][1].Side(4)
        && br.bricks[2][2][1].Side(4) == br.bricks[1][2][1].Side(4)
        && br.bricks[1][2][2].Side(4) != br.bricks[1][2][1].Side(4)
        && br.bricks[1][2][0].Side(4) != br.bricks[1][2][1].Side(4)) {
            turnThrough(0,1);
            pifpaf1();
            turnThrough(0,-1);
        }
        else if (br.bricks[0][2][1].Side(4) == br.bricks[1][2][1].Side(4)
                 && br.bricks[2][2][1].Side(4) != br.bricks[1][2][1].Side(4)
                 && br.bricks[1][2][2].Side(4) == br.bricks[1][2][1].Side(4)
                 && br.bricks[1][2][0].Side(4) != br.bricks[1][2][1].Side(4)) {
            turnThrough(0,1);
            pifpaf1();
            pifpaf1();
            turnThrough(0,-1);
        }
        else if (br.bricks[0][2][1].Side(4) != br.bricks[1][2][1].Side(4)
        && br.bricks[2][2][1].Side(4) != br.bricks[1][2][1].Side(4)
        && br.bricks[1][2][2].Side(4) != br.bricks[1][2][1].Side(4)
        && br.bricks[1][2][0].Side(4) != br.bricks[1][2][1].Side(4)) {
            turnThrough(0,1);
            pifpaf1();
            turnThrough(0,-1);
            turnHor(2,-1);
            turnHor(2,-1);
            turnThrough(0,1);
            pifpaf1();
            pifpaf1();
            turnThrough(0,-1);
        }
        else {
            turnHor(0,-1);
            turnHor(1,-1);
            turnHor(2,-1);
        }
        if (check_nn_cross()) {
            break;
        }
    }
    std::cout << "up nn cross solved\n";
}

bool CubeDlg::check_level1() {
    int check = 0;
    (br.bricks[0][0][0].Side(4) == br.bricks[1][0][1].Side(4) ? check++ : NULL);
    (br.bricks[0][0][2].Side(4) == br.bricks[1][0][1].Side(4) ? check++ : NULL);
    (br.bricks[2][0][0].Side(4) == br.bricks[1][0][1].Side(4) ? check++ : NULL);
    (br.bricks[2][0][2].Side(4) == br.bricks[1][0][1].Side(4) ? check++ : NULL);
    if (check == 4) {
        return true;
    }
    return false;
}

bool CubeDlg::check_level2() {
    int check = 0;
    (br.bricks[0][1][0].Side(0) == br.bricks[1][1][0].Side(0) ? check++ : NULL);
    (br.bricks[2][1][0].Side(0) == br.bricks[1][1][0].Side(0) ? check++ : NULL);
    (br.bricks[0][1][2].Side(2) == br.bricks[1][1][2].Side(2) ? check++ : NULL);
    (br.bricks[2][1][2].Side(2) == br.bricks[1][1][2].Side(2) ? check++ : NULL);
    (br.bricks[0][1][0].Side(1) == br.bricks[0][1][1].Side(1) ? check++ : NULL);
    (br.bricks[2][1][0].Side(3) == br.bricks[2][1][1].Side(3) ? check++ : NULL);
    (br.bricks[0][1][2].Side(1) == br.bricks[0][1][1].Side(1) ? check++ : NULL);
    (br.bricks[2][1][2].Side(3) == br.bricks[2][1][1].Side(3) ? check++ : NULL);
    if (check == 8) {
        return true;
    }
    return false;
}

void CubeDlg::CRUP2() {
    while (!check_level3up()) {
        if (br.bricks[0][2][2].Side(5) == br.bricks[0][1][1].Side(1)) {
            for (int i = 0; i < 4; i++) {
                pifpaf1();
            }
        }
        else if (br.bricks[0][2][2].Side(2) == br.bricks[0][1][1].Side(1)) {
            for (int i = 0; i < 2; i++) {
                pifpaf1();
            }
        }
        turnVer(0,-1);
    }
    std::cout << "3levelup solved\n";

}

bool CubeDlg::check_level3up() {
    int check = 0;
    for (int y = 0; y < 3; y++) {
        for (int z = 0; z < 3; z++) {
            if (br.bricks[0][y][z].Side(1) == br.bricks[0][1][1].Side(1)) {
                check++;
            }
        }
    }
    if (check == 9) {
        return true;
    }
    return false;
}

void CubeDlg::vertexlvl3() {
    int count = 0;
    while (!check_vertexlvl3()) {
        while (count < 2) {
            count = 0;
            turnHor(2,-1);
            (br.bricks[0][2][1].Side(1) == br.bricks[0][1][1].Side(1) ? count++ : NULL);
            (br.bricks[1][2][0].Side(0) == br.bricks[1][1][0].Side(0) ? count++ : NULL);
            (br.bricks[1][2][2].Side(2) == br.bricks[1][1][2].Side(2) ? count++ : NULL);
            (br.bricks[2][2][1].Side(3) == br.bricks[2][1][1].Side(3) ? count++ : NULL);
        }
        if (br.bricks[1][2][0].Side(0) == br.bricks[2][1][1].Side(3)
        && br.bricks[2][2][1].Side(3) == br.bricks[1][1][0].Side(0)) {
            turnVer(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnThrough(0,-1);
            turnVer(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnHor(2,1);
            turnVer(2,1);
            turnThrough(0,1);
            turnVer(2,-1);
            turnVer(2,-1);
            turnHor(2,1);
            turnVer(2,1);
            turnHor(2,1);
        }
        else if (br.bricks[2][2][1].Side(3) == br.bricks[0][1][1].Side(1)
             && br.bricks[0][2][1].Side(1) == br.bricks[2][1][1].Side(3)) {
            turnVer(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnThrough(0,-1);
            turnVer(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnHor(2,1);
            turnVer(2,1);
            turnThrough(0,1);
            turnVer(2,-1);
            turnVer(2,-1);
            turnHor(2,1);
            turnVer(2,1);
            turnHor(2,1);
            turnHor(2,-1);
            turnHor(2,-1);
            turnVer(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnThrough(0,-1);
            turnVer(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnHor(2,1);
            turnVer(2,1);
            turnThrough(0,1);
            turnVer(2,-1);
            turnVer(2,-1);
            turnHor(2,1);
            turnVer(2,1);
            turnHor(2,1);
            turnHor(2,1);
        }
        turnHor(2,-1);
        turnHor(1,-1);
        turnHor(0,-1);
    }
    std::cout << "lvl3 vertex solved\n";
}

bool CubeDlg::check_vertexlvl3() {
    int check = 0;
    (br.bricks[0][2][1].Side(1) == br.bricks[0][1][1].Side(1) ? check++ : NULL);
    (br.bricks[1][2][0].Side(0) == br.bricks[1][1][0].Side(0) ? check++ : NULL);
    (br.bricks[1][2][2].Side(2) == br.bricks[1][1][2].Side(2) ? check++ : NULL);
    (br.bricks[2][2][1].Side(3) == br.bricks[2][1][1].Side(3) ? check++ : NULL);
    if (check == 4){
        return true;
    }
    return false;
}

bool CubeDlg::check_solved() {
    return false;
}

void CubeDlg::edgelvl3() {
    while (!check_edgeslvl3()) {
        for (int k = 0; k < 4; k++) {
            if (br.bricks[0][2][2].Side(1) == br.bricks[0][1][1].Side(1)
            && br.bricks[0][2][2].Side(2) == br.bricks[1][1][2].Side(2)) {
                break;
            }
            turnHor(2,-1);
            turnHor(1,-1);
            turnHor(0,-1);
        }
            turnThrough(0,-1);
            turnThrough(1,-1);
            turnThrough(2,-1);

            turnHor(2,-1);
            turnHor(2,-1);
            turnVer(2,-1);
            turnHor(2,-1);
            turnHor(2,-1);
            turnVer(2,1);
            turnThrough(0,1);
            turnThrough(0,1);
            turnHor(2,-1);
            turnHor(2,-1);
            turnVer(0,-1);
            turnHor(2,-1);
            turnHor(2,-1);
            turnVer(0,1);
            turnThrough(0,1);
            turnThrough(0,1);

            turnThrough(0,1);
            turnThrough(1,1);
            turnThrough(2,1);
    }
    std::cout << "solved\n";
}

bool CubeDlg::check_edgeslvl3() {
    int check = 0;
    (br.bricks[0][2][0].Side(4) == br.bricks[1][2][1].Side(4) ? check++ : NULL);
    (br.bricks[0][2][2].Side(4) == br.bricks[1][2][1].Side(4) ? check++ : NULL);
    (br.bricks[2][2][0].Side(4) == br.bricks[1][2][1].Side(4) ? check++ : NULL);
    (br.bricks[2][2][2].Side(4) == br.bricks[1][2][1].Side(4) ? check++ : NULL);

    (br.bricks[0][2][0].Side(0) == br.bricks[1][1][0].Side(0) ? check++ : NULL);
    (br.bricks[0][2][0].Side(1) == br.bricks[0][1][1].Side(1) ? check++ : NULL);

    (br.bricks[0][2][2].Side(1) == br.bricks[0][1][1].Side(1) ? check++ : NULL);
    (br.bricks[0][2][2].Side(2) == br.bricks[1][1][2].Side(2) ? check++ : NULL);

    (br.bricks[2][2][0].Side(0) == br.bricks[1][1][0].Side(0) ? check++ : NULL);
    (br.bricks[2][2][0].Side(3) == br.bricks[2][1][1].Side(3) ? check++ : NULL);

    (br.bricks[2][2][2].Side(3) == br.bricks[2][1][1].Side(3) ? check++ : NULL);
    (br.bricks[2][2][2].Side(2) == br.bricks[1][1][2].Side(2) ? check++ : NULL);

    if (check == 12) {
        return true;
    }
    return false;
}


