#include "cubeDLG.h"

int main() {
    CubeDlg Screen;
    Screen.init();
    float x = 1, y = 1, z = 1;
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
        if (glfwGetKey(Screen.window, GLFW_KEY_9)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_9)) {
                Screen.br.shuffle();
            }
        }
        //test
        if (glfwGetKey(Screen.window, GLFW_KEY_A)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_A)) {
                Screen.br.turnVer(0,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_S)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_S)) {
                Screen.br.turnVer(1,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_D)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_D)) {
                Screen.br.turnVer(2,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_Q)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_Q)) {
                Screen.br.turnVer(0,1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_W)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_W)) {
                Screen.br.turnVer(1,1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_E)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_E)) {
                Screen.br.turnVer(2,1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_R)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_R)) {
                Screen.br.turnHor(0,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_T)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_T)) {
                Screen.br.turnHor(1,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_Y)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_Y)) {
                Screen.br.turnHor(2,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_F)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_F)) {
                Screen.br.turnHor(0,1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_G)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_G)) {
                Screen.br.turnHor(1,1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_H)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_H)) {
                Screen.br.turnHor(2,1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_U)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_U)) {
                Screen.br.turnThrough(2,-1);
            }
        }
        if (glfwGetKey(Screen.window, GLFW_KEY_J)) {
            if (!glfwGetKey(Screen.window, GLFW_KEY_J)) {
                Screen.br.turnThrough(2,1);
            }
        }
        Screen.drawScene(x,y,z);
        glfwPollEvents();
    }
    while( glfwGetKey(Screen.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(Screen.window) == 0 );
    glfwTerminate();
}




//if (glfwGetKey(Screen.window, GLFW_KEY_9)) {
//if (!glfwGetKey(Screen.window, GLFW_KEY_9)) {
//Screen.br.turnHor(0,-1);
//}
//}
//if (glfwGetKey(Screen.window, GLFW_KEY_0)) {
//if (!glfwGetKey(Screen.window, GLFW_KEY_0)) {
//Screen.br.turnVer(0,-1);
//}
//}
//if (glfwGetKey(Screen.window, GLFW_KEY_O)) {
//if (!glfwGetKey(Screen.window, GLFW_KEY_O)) {
//Screen.br.turnHor(0,1);
//}
//}
//if (glfwGetKey(Screen.window, GLFW_KEY_P)) {
//if (!glfwGetKey(Screen.window, GLFW_KEY_P)) {
//Screen.br.turnVer(0,1);
//}
//}