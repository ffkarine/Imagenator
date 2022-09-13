#include <iostream>
#include "Figures.h"
#include <GLFW/glfw3.h>
#include <glut.h>

//#include "Canvas.h"

using namespace std;

bool canvasAssigned = false;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    // Rescale to "pixel" scale - position (x, y) is x pixels along, y pixels up
    // Allows user to resize window without stretching UI elements
    glScalef((double)(800) / (double)(glutGet(GLUT_WINDOW_WIDTH)), (double)(600) / (double)(glutGet(GLUT_WINDOW_HEIGHT)), 1.0f);

    // Draw the canvas and any overlays from tools in use
    if (canvasAssigned) {
        //currentCanvas.Draw(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
        //ToolEvents::Display(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    }

    // Draw the dark semi-transparent cover if necessary
    //Cover::Display(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

    // Draw mouse pointer last (so it appears above everything else)
    //Display_Pointer();

    glPopMatrix();
    glutSwapBuffers();
}

void init()
{
    // Enable transparency (e.g. black semi-transparent cover over screen appears with dialogues)
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set initial scale for window coordinates
    //gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

int main(void) {
    GLFWwindow* window;
    int command;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
        glLoadIdentity(); //Reset the drawing perspective

        glBegin(GL_LINES);
        glVertex2f(.0, .0);
        glVertex2f(1, 1);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //cout << "Escolha uma opção:\n";
    //cout << "1 - Desenhar forma geométrica:";
    //cin >> command;

    //if (command == 1) {
    //    cout << "desenhar";
    //}

    glfwTerminate();
    return 0;
}