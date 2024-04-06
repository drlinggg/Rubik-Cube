#include "cubeDLG.h"

int main() {
    CubeDlg Screen;
    Screen.init();
    float x = -1; float y = -1; float z = -1;
    do {
        if (glfwGetKey(Screen.window, GLFW_KEY_1)) {
            x = 1, y = 1, z = 1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_2)) {
            x = 1, y = 1, z = -1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_3)) {
            x = -1, y = 1, z = -1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_4)) {
            x = -1, y = 1, z = 1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_5)) {
            x = 1, y = -1, z = 1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_6)) {
            x = 1, y = -1, z = -1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_7)) {
            x = -1, y = -1, z = -1;
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_8)) {
            x = -1, y = -1, z = 1;
        }
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        glFinish();
        Screen.drawScene(x,y,z);
        glfwPollEvents();
    }
    while( glfwGetKey(Screen.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(Screen.window) == 0 );
}