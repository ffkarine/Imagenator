#include <iostream>
#include <math.h>
#include <vector>

#include <GLFW/glfw3.h>
#include <glut.h>

#define AXIS_TICK_REFERENCE 11

using namespace std;

bool canvasAssigned = false;

class Shape {
public:
    GLFWwindow* shapeWindow;
    float origin_X, origin_Y, center_X, center_Y, edgeLenght;
    vector<float> coordinates_X;
    vector<float> coordinates_Y;

    void drawShape()
    {
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < coordinates_X.size(); i++)
            glVertex2f(coordinates_X[i], coordinates_Y[i]);

        glEnd();
    }
};

class Square : public Shape {
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do quadrado
    Square(float center_Xc, float center_Yc, float edgeLenghtc, GLFWwindow* window)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;
        shapeWindow = window;

        origin_X = center_X - edgeLenght / 2;
        origin_Y = center_Y - edgeLenght / 2;

        calculateVertices();
    }

    void calculateVertices()
    {
        //int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));

        //glfwGetWindowSize(shapeWindow, w, h);

        coordinates_X.push_back((origin_X) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + edgeLenght) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + edgeLenght) / AXIS_TICK_REFERENCE);
    }
};

class Triangle : public Shape
{
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do triângulo
    Triangle(float center_Xc, float center_Yc, float edgeLenghtc, GLFWwindow* window)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;
        shapeWindow = window;

        origin_X = center_X - edgeLenght / 2;
        origin_Y = center_Y - edgeLenght / 3;

        calculateVertices();
    }

    void calculateVertices()
    {
        //int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));

        //glfwGetWindowSize(shapeWindow, w, h);

        float triangleHeight = sqrt(3) * edgeLenght / 2;

        coordinates_X.push_back((origin_X) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght / 2) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + triangleHeight) / AXIS_TICK_REFERENCE);
    }
};

class Hexagon : public Shape
{
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do hexágono
    Hexagon(float center_Xc, float center_Yc, float edgeLenghtc, GLFWwindow* window)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;

        origin_X = center_X - edgeLenght / 2;
        origin_Y = center_Y - edgeLenght * sqrt(3) / 2;

        calculateVertices();
    }

    void calculateVertices()
    {
        float halfEdgeLenght = edgeLenght / 2;
        float edgeHeight = sqrt(3) * halfEdgeLenght;

        coordinates_X.push_back((origin_X) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght + halfEdgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + edgeHeight) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X + edgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + edgeHeight + edgeHeight) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + edgeHeight + edgeHeight) / AXIS_TICK_REFERENCE);

        coordinates_X.push_back((origin_X - halfEdgeLenght) / AXIS_TICK_REFERENCE);
        coordinates_Y.push_back((origin_Y + edgeHeight) / AXIS_TICK_REFERENCE);
    }
};

void drawAxis(GLFWwindow* window)
{
    // width; height
    int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));
    int tickSize = 10;

    glfwGetWindowSize(window, w, h);

    glBegin(GL_LINES);

    //Eixo X principal
    glVertex2f(-1, 0);
    glVertex2f(1, 0);

    //Eixo Y principal
    glVertex2f(0, -1);
    glVertex2f(0, 1);

    //Ticks dos eixos
    for (int i = -10; i <= 10; i++)
    {
        // Ticks eixo X
        glVertex2f((float(i) / AXIS_TICK_REFERENCE), float(-tickSize) / (*h));
        glVertex2f((float(i) / AXIS_TICK_REFERENCE), float(tickSize) / (*h));

        // Ticks eixo Y
        glVertex2f(float(-tickSize) / (*w), (float(i) / AXIS_TICK_REFERENCE));
        glVertex2f(float(tickSize) / (*w), (float(i) / AXIS_TICK_REFERENCE));
    }


    glEnd();

    free(w);
    free(h);
}

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

//Initial prompt for basic option selection
int prompt() {
    int mainOption;

    cout << "Choose your option:" << endl;
    cout << "1 - Draw Figure" << endl;
    cout << "2 - Transform Figure" << endl;
    cout << "3 - Delete Figure" << endl;
    cin >> mainOption;

    return mainOption;
}

//Prompt for type of input for new shape
int promptInput() {
    int inputOption;

    cout << "\nChoose how to input the points:" << endl;
    cout << "1 - Type points" << endl;
    cout << "2 - Click on Screen" << endl;
    cout << "3 - Type center and size" << endl;
    cin >> inputOption;

    return inputOption;
}

int main(void) {
    GLFWwindow* window;
    int command;
    //Vector for controling the number of shapes after adding or excluding
    vector<int> figures;
    int control = 0;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Imagenator", NULL, NULL);
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

        drawAxis(window);

        //Initial prompt for basic option selection
        int mainOption = prompt();

        //If adding shape option was selected
        if (mainOption == 1) {
            //verify current number of shapes
            if (figures.size() == 5) {
                cout << "\nReached max number of figures" << endl;
            }
            else {
                //Prompt for type of input for new shape
                int inputOption = promptInput();

                //If option of typing center coordinates and size was selected
                if (inputOption == 3) {
                    int shapeOption;
                    float centerX, centerY, size;

                    cout << "\nChoose Figure Type:" << endl;
                    cout << "1 - Rectangle" << endl;
                    cout << "2 - Triangle" << endl;
                    cout << "3 - Hexagon" << endl;
                    cin >> shapeOption;

                    cout << "\nType center (X and Y):" << endl;
                    cin >> centerX >> centerY;

                    cout << "\nType size:" << endl;
                    cin >> size;

                    //Limit coordinates and size to be inside the screen
                    while (((centerX > 10) or (centerX < -10)) or ((centerY > 10) or (centerY < -10)) or (size > 10)) {
                        cout << "\nCoordinates and size must be in the interval of -10 and 10, type X and Y again:" << endl;
                        cin >> centerX >> centerY;

                        cout << "\nType size:" << endl;
                        cin >> size;
                    }

                    //Call drawing methods for each option and adding 1 to the control vector
                    if (shapeOption == 1) {
                        Square s = Square(centerX, centerY, size, window);
                        s.drawShape();
                        
                        figures.push_back(1);
                    }
                    else if (shapeOption == 2) {
                        Triangle t = Triangle(centerX, centerY, size, window);
                        t.drawShape();
                        figures.push_back(1);
                    }
                    else if (shapeOption == 3) {
                        Hexagon h = Hexagon(centerX, centerY, size, window);
                        h.drawShape();
                        figures.push_back(1);
                    }
                }
                else{
                    cout << "fazer o resto kkk";
                }
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        control += 1;
        ///////////////////////////////////////////////////////////////////////////////////////
        ///// LEMBRAR DE LIMITAR AS ENTRADAS SOMENTE PARA O INTERVALO DOS EIXOS (-10, 10) /////
        ///////////////////////////////////////////////////////////////////////////////////////

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