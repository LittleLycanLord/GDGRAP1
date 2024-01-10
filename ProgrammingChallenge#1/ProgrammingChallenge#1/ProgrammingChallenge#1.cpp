#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#include "math.h"

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(480, 480, "Pentagon", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POLYGON);

        //? https://mathworld.wolfram.com/RegularPentagon.html
        glVertex2f(0.0f, 1.0f);
        glVertex2f(sin((2 * M_PI) / 5), cos((2 * M_PI) / 5));
        glVertex2f(sin((4 * M_PI) / 5), -cos((M_PI) / 5));
        glVertex2f(-sin((4 * M_PI) / 5), -cos((M_PI) / 5));
        glVertex2f(-sin((2 * M_PI) / 5), cos((2 * M_PI) / 5));
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}