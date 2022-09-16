#include <iostream>
#include <math.h>
#include <vector>

#include <GLFW/glfw3.h>
#include <glut.h>

#define CANVAS_SIZE 10
#define AXIS_TICK_REFERENCE (CANVAS_SIZE + 1)
#define MAX_FIGURES 5


using namespace std;

bool canvasAssigned = false;

class Shape {
public:
    GLFWwindow* shapeWindow;
    float origin_X, origin_Y, center_X, center_Y, edgeLenght;
    vector<float> coordinates_X;
    vector<float> coordinates_Y;

    Shape() = default;

    Shape(vector<float> x, vector<float> y)
    {
        for (int i = 0; i < x.size(); i++)
        {
            coordinates_X.push_back(x[i] / AXIS_TICK_REFERENCE);
            coordinates_Y.push_back(y[i] / AXIS_TICK_REFERENCE);
        }
    }

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

    cout << "\nChoose your option:" << endl;
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
    vector<Shape> shapes;
    vector<float> x_shape;
    vector<float> y_shape;
    int control = 0, inputOption = 0, mainOption = 0, auxInput = 0;
    float auxX, auxY;

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
        mainOption = prompt();

        //If adding shape option was selected
        if (mainOption == 1) {
            //verify current number of shapes
            if (shapes.size() == MAX_FIGURES) {
                cout << "\nReached max number of figures" << endl;
            }
            else {
                //Prompt for type of input for new shape
                inputOption = promptInput();

                if (inputOption == 1)
                {
                    while (auxInput != 2)
                    {
                        cout << "\n1 - New point" << endl;
                        cout << "2 - Stop Drawing (If less than 3 points were entered no drawing will be generated)." << endl;
                        cin >> auxInput;

                        if (auxInput == 1)
                        {
                            cout << "X : ";
                            cin >> auxX;

                            cout << "Y : ";
                            cin >> auxY;

                            while (((auxX > CANVAS_SIZE) or (auxX < -CANVAS_SIZE)) or ((auxY > CANVAS_SIZE) or (auxY < -CANVAS_SIZE))) {
                                cout << "\nCoordinates and size must be in the interval of -" << CANVAS_SIZE << " and " << CANVAS_SIZE << ", type X and Y again:" << endl;
                                cin >> auxX >> auxY;
                            }

                            x_shape.push_back(auxX);
                            y_shape.push_back(auxY);
                        }
                    }

                    if (x_shape.size() < 3)
                        cout << "\nLess than 3 points entered. NO drawing will be generated!" << endl;

                    else
                    {
                        Shape sh = Shape(x_shape, y_shape);
                        shapes.push_back(sh);
                    }

                    x_shape.clear();
                    y_shape.clear();
                    auxInput = 0;
                }

                //If option of typing center coordinates and size was selected
                else if (inputOption == 3) {
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
                    while (((centerX > CANVAS_SIZE) or (centerX < -CANVAS_SIZE)) or ((centerY > CANVAS_SIZE) or (centerY < -CANVAS_SIZE)) or (size > CANVAS_SIZE)) {
                        cout << "\nCoordinates and size must be in the interval of -" << CANVAS_SIZE << " and " << CANVAS_SIZE << ", type X and Y again:" << endl;
                        cin >> centerX >> centerY;

                        cout << "\nType size:" << endl;
                        cin >> size;
                    }

                    //Call drawing methods for each option and adding 1 to the control vector
                    if (shapeOption == 1) {
                        Square s = Square(centerX, centerY, size, window);
                        shapes.push_back(s);
                    }
                    else if (shapeOption == 2) {
                        Triangle t = Triangle(centerX, centerY, size, window);
                        shapes.push_back(t);
                    }
                    else if (shapeOption == 3) {
                        Hexagon h = Hexagon(centerX, centerY, size, window);
                        shapes.push_back(h);
                    }
                }
                else{
                    cout << "fazer o resto kkk";
                }
            }
        }

        for (int i = 0; i < shapes.size(); i++)
            shapes[i].drawShape();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        control += 1;

        ///////////////////////////////////////////////////////////////////////////////////////

        /////                     PROIBIR INPUT DE PONTOS IGUAIS                          /////

        ///////////////////////////////////////////////////////////////////////////////////////

    }

    glfwTerminate();
    return 0;
}