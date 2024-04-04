#include "cube.cpp"

int main() {

    //инициализация glfw
    if( !glfwInit() ){
        std::cout << "no glfw init";
        return -1;
    }

    //создать окно
    GLFWwindow* window;
    window = glfwCreateWindow( 1024, 768, "Rubic Cube", NULL, NULL);
    if( window == NULL ){
        std::cout << "OpenGL 2.1.n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //инициализация GLEW
    glewExperimental=true; // Флаг необходим в Core-режиме OpenGL
    if (glewInit() != GLEW_OK) {
        std::cout << "no glew init";
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //цикл действия программы
    do{
        // Пока что ничего не выводим. Это будет в уроке 2.

        // Сбрасываем буферы
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Проверяем нажатие клавиши Escape или закрытие окна
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return 0;
}