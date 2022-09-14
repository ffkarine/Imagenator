#include <iostream>
#include <math.h>
#include <vector>

#include "Figures.h"
#include <GLFW/glfw3.h>
#include <glut.h>

//#include "Canvas.h"

using namespace std;

class Shape {
    public:
        float origin_X, origin_Y, center_X, center_Y, edgeLenght;
        vector<float> coordinates_X;
        vector<float> coordinates_Y;
};

class Square : public Shape {
    public:
        // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do quadrado
        Square(float center_Xc, float center_Yc, float edgeLenghtc)
        {
            center_X = center_Xc;
            center_Y = center_Yc;
            edgeLenght = edgeLenghtc;

            origin_X = center_X - edgeLenght/2;
            origin_Y = center_Y - edgeLenght/2;
        }

        void DrawSquare(GLFWwindow* window)
        {
            // width; height
            int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));

            glfwGetWindowSize(window, w, h);

            //Normalizes the square's origin point
            origin_X = (float)origin_X / (*w);
            origin_Y = (float)origin_Y / (*h);

            glBegin(GL_LINES);

            glVertex2f(origin_X, origin_Y);
            glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y);

            glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y);
            glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y + float(edgeLenght) / (*h));

            glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y + float(edgeLenght) / (*h));
            glVertex2f(origin_X, origin_Y + float(edgeLenght) / (*h));

            glVertex2f(origin_X, origin_Y + float(edgeLenght) / (*h));
            glVertex2f(origin_X, origin_Y);

            glEnd();

            free(w);
            free(h);
        }
};

class Triangle : public Shape
{
    public:
        // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do triângulo
        Triangle(float center_Xc, float center_Yc, float edgeLenghtc)
        {
            center_X = center_Xc;
            center_Y = center_Yc;
            edgeLenght = edgeLenghtc;

            origin_X = center_X - edgeLenght/2;
            origin_Y = center_Y - edgeLenght/3;
        }   

        void DrawTriangle(GLFWwindow* window)
        {
            // width; height
            int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));
            float triangleHeight = 0;

            glfwGetWindowSize(window, w, h);

            //Normalizes the triangle's origin point
            origin_X = (float)origin_X / (*w);
            origin_Y = (float)origin_Y / (*h);

            triangleHeight = sqrt(3) * edgeLenght / 2;

            glBegin(GL_LINES);

            glVertex2f(origin_X, origin_Y);
            glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y);

            glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y);
            glVertex2f(origin_X + (float(edgeLenght) / (*w)) / 2, origin_Y + float(triangleHeight) / (*h));

            glVertex2f(origin_X + (float(edgeLenght) / (*w)) / 2, origin_Y + float(triangleHeight) / (*h));
            glVertex2f(origin_X, origin_Y);

            glEnd();

            free(w);
            free(h);
        }
};

class Hexagon : public Shape
{
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do triângulo
    Hexagon(float center_Xc, float center_Yc, float edgeLenghtc)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;

        origin_X = center_X - edgeLenght/2;
        origin_Y = center_Y - edgeLenght*sqrt(3)/2;
    }

    void DrawHexagon(GLFWwindow* window)
    {
        // width; height
        int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));
        float edgeHeight = 0, halfEdgeLenght = 0;

        glfwGetWindowSize(window, w, h);

        //Normalizes the triangle's origin point
        origin_X = (float)origin_X / (*w);
        origin_Y = (float)origin_Y / (*h);

        halfEdgeLenght = edgeLenght / 2;
        edgeHeight = sqrt(3) * halfEdgeLenght;

        glBegin(GL_LINES);

        glVertex2f(origin_X, origin_Y);
        glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y);

        glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y);
        glVertex2f(origin_X + float(edgeLenght + halfEdgeLenght) / (*w), origin_Y + float(edgeHeight) / (*h));

        glVertex2f(origin_X + float(edgeLenght + halfEdgeLenght) / (*w), origin_Y + float(edgeHeight) / (*h));
        glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y + float(edgeHeight + edgeHeight) / (*h));

        glVertex2f(origin_X + float(edgeLenght) / (*w), origin_Y + float(edgeHeight + edgeHeight) / (*h));
        glVertex2f(origin_X, origin_Y + float(edgeHeight + edgeHeight) / (*h));

        glVertex2f(origin_X, origin_Y + float(edgeHeight + edgeHeight) / (*h));
        glVertex2f(origin_X - float(halfEdgeLenght) / (*w), origin_Y + float(edgeHeight) / (*h));

        glVertex2f(origin_X - float(halfEdgeLenght) / (*w), origin_Y + float(edgeHeight) / (*h));
        glVertex2f(origin_X, origin_Y);

        glEnd();

        free(w);
        free(h);
    }

};

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

        //glBegin(GL_LINES);
        //glVertex2f(.0, .0);
        //glVertex2f(1, 1);
        //glEnd();

        //DrawSquare(window, -250, -250, 200);
        //DrawTriangle(window, 100, -250, 200);
        //DrawHexagon(window, 0, 0, 200);

        Square s = Square(0, 0, 400);
        s.DrawSquare(window);

        Triangle t = Triangle(0, 0, 400);
        t.DrawTriangle(window);

        Hexagon h = Hexagon(0, 0, 400);
        h.DrawHexagon(window);

        //DrawTriangle(window, 100, -250, 200);
        //DrawHexagon(window, 0, 0, 200);

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