#include "cubeDLG.h"

int main() {
    CubeDlg Screen;
    Screen.init();
    glEnable(GL_DEPTH_TEST);
    do {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glFinish();
        Screen.drawScene();
        glfwPollEvents();
    }
    while( glfwGetKey(Screen.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(Screen.window) == 0 );
}