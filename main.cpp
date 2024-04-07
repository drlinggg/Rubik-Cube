#include "cubeDLG.h"

int main() {
    CubeDlg Screen;
    Screen.init();
    do {
        Screen.processInput();
        Screen.drawScene();
        glfwPollEvents();
    }
    while( glfwGetKey(Screen.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(Screen.window) == 0 );
    glfwTerminate();
}