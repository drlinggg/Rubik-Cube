#include "cubeDLG.h"
//GLFWwindow* window;

int main() {
    CubeDlg smh;
    smh.init();
    do {
        smh.drawScene();
        glfwPollEvents();
    }
    while( glfwGetKey(smh.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(smh.window) == 0 );
}