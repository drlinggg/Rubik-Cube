#include "cubeDLG.h"
//GLFWwindow* window;

int main() {
    CubeDlg smh;
    smh.init();
    do {
        smh.drawScene();
        GLuint VertexArrayID;
        glGenVertexArrays(1, &VertexArrayID);
        glBindVertexArray(VertexArrayID);
        glfwPollEvents();
        static const GLfloat g_vertex_buffer_data[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
        };
        // Это будет идентификатором нашего буфера вершин
        GLuint vertexbuffer;
        // Создадим 1 буфер и поместим в переменную vertexbuffer его идентификатор
        glGenBuffers(1, &vertexbuffer);
        // Сделаем только что созданный буфер текущим
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        // Передадим информацию о вершинах в OpenGL
        glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
        // Указываем, что первым буфером атрибутов будут вершины
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // Атрибут 0. Подробнее об этом будет рассказано в части, посвященной шейдерам.
                3,                  // Размер
                GL_FLOAT,           // Тип
                GL_FALSE,           // Указывает, что значения не нормализованы
                0,                  // Шаг
                (void*)0            // Смещение массива в буфере
        );
        // Вывести треугольник!
        glDrawArrays(GL_TRIANGLES, 0, 3); // Начиная с вершины 0, всего 3 вершины -> один треугольник
        glDisableVertexAttribArray(0);
        glFinish();
        glfwSwapBuffers(smh.window);
    }
    while( glfwGetKey(smh.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                 glfwWindowShouldClose(smh.window) == 0 );
}