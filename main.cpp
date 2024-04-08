#include "cubeDLG.h"

int main() {
    CubeDlg Screen;
    Screen.init();
    do {
        Screen.processInput();
        Screen.drawScene();
        glfwPollEvents();
    }
    while( glfwGetKey(Screen.getWindow(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(Screen.getWindow()) == 0 );
    glfwTerminate();
}