#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <endian.h>
#include <leif/leif.h>
#include <stdbool.h>
#include <stdlib.h>

#include "headers/conf.h"
#include "headers/gui.h"
#include "headers/theme.h"
#include "headers/fonts.h"

void check(void *ptr)
{
    if (!ptr) {
        glfwTerminate();
        exit(-1);
    }
}

LfTheme theme_set()
{
    LfTheme theme = lf_get_theme();
    theme.div_props.color = LF_NO_COLOR;
    return theme;
}

int main()
{
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    GLFWwindow *win = glfwCreateWindow(appM.width, appM.height, "NekoNeko1", NULL, NULL);
    check(win);
    glfwMakeContextCurrent(win);

    lf_init_glfw(appM.width, appM.height, win);
    init_theme();
    lf_set_theme(theme_set());


    while (!glfwWindowShouldClose(win)) {
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        lf_begin();
        work_leif(&appM);
        lf_end();

        glfwPollEvents();
        glfwSwapBuffers(win);
    }

    freefonts();
    lf_terminate();
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}

