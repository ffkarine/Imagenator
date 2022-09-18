#define _USE_MATH_DEFINES

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
    double origin_X, origin_Y, center_X, center_Y, edgeLenght;
    vector<double> coordinates_X;
    vector<double> coordinates_Y;

    Shape() = default;

    Shape(vector<double> x, vector<double> y)
    {
        for (int i = 0; i < x.size(); i++)
        {
            coordinates_X.push_back(x[i]);
            coordinates_Y.push_back(y[i]);
        }
    }

    void drawShape()
    {
        glBegin(GL_LINE_LOOP);

        for (int i = 0; i < coordinates_X.size(); i++)
            glVertex2f(coordinates_X[i], coordinates_Y[i]);

        glEnd();
    }

    void setCenter(double newCenter_X, double newCenter_Y)
    {
        center_X = newCenter_X;
        center_Y = newCenter_Y;
    }

    void setOrigin(double newOrigin_X, double newOrigin_Y)
    {
        origin_X = newOrigin_X;
        origin_Y = newOrigin_Y;
    }

    virtual void calculateVertices() {};

    virtual void translateShape(double increment_X, double increment_Y)
    {
        setCenter(center_X + increment_X, center_Y + increment_Y);
        setOrigin(origin_X + increment_X, origin_Y + increment_Y);

        for (int i = 0; i < coordinates_X.size(); i++)
        {
            coordinates_X[i] = coordinates_X[i] + increment_X;
            coordinates_Y[i] = coordinates_Y[i] + increment_Y;
        }
    }

    virtual void rotateShape(double rotAngleDeg)
    {
        double auxCenter_X = center_X, auxCenter_Y = center_Y;
        double auxX, auxY;

        double sinA = sin(rotAngleDeg * M_PI / 180);
        double cosA = cos(rotAngleDeg * M_PI / 180);

        this->translateShape(-center_X, -center_Y);

        double newCenter_X = ( ((center_X) * cosA) - ((center_Y) * sinA) );
        double newCenter_Y = ( ((center_X) * sinA) + ((center_Y) * cosA) );

        double newOrigin_X = ( ((origin_X) * cosA) - ((origin_Y) * sinA) );
        double newOrigin_Y = ( ((origin_X) * sinA) + ((origin_Y) * cosA) );

        for (int i = 0; i < coordinates_X.size(); i++)
        {
            auxX = coordinates_X[i];
            auxY = coordinates_Y[i];

            coordinates_X[i] = ( (auxX * cosA) - (auxY * sinA) );
            coordinates_Y[i] = ( (auxX * sinA) + (auxY * cosA) );
        }

        setCenter(newCenter_X, newCenter_Y);
        setOrigin(newOrigin_X, newOrigin_Y);

        this->translateShape(auxCenter_X, auxCenter_Y);
    }

    virtual void scaleShape(double scalingFactor)
    {
        for (int i = 0; i < coordinates_X.size(); i++)
        {
            coordinates_X[i] = coordinates_X[i] * scalingFactor;
            coordinates_Y[i] = coordinates_Y[i] * scalingFactor;
        }

        setCenter(center_X * scalingFactor, center_Y * scalingFactor);
        setOrigin(origin_X * scalingFactor, origin_Y * scalingFactor);
    }

    virtual void shearShape(char axis, double shearingFactor)
    {
        if (axis == 'X' or axis == 'x')
        {
            for (int i = 0; i < coordinates_X.size(); i++)
            {
                coordinates_X[i] = coordinates_X[i] + coordinates_Y[i] * shearingFactor;
            }

            setCenter(center_X + center_Y * shearingFactor, center_Y);
            setOrigin(origin_X + origin_Y * shearingFactor, origin_Y);
        }

        else if (axis == 'Y' or axis == 'y')
        {
            for (int i = 0; i < coordinates_X.size(); i++)
            {
                coordinates_Y[i] = coordinates_Y[i] + coordinates_X[i] * shearingFactor;
            }

            setCenter(center_X, center_Y + center_X * shearingFactor);
            setOrigin(origin_X, origin_Y + origin_X * shearingFactor);
        }
    }

    virtual void mirrorShape(char axis)
    {
        if (axis == 'X' or axis == 'x')
        {
            for (int i = 0; i < coordinates_X.size(); i++)
            {
                coordinates_Y[i] = coordinates_Y[i] * -1;
            }

            setCenter(center_X, center_Y * -1);
            setOrigin(origin_X, origin_Y * -1);
        }

        else if (axis == 'Y' or axis == 'y')
        {
            for (int i = 0; i < coordinates_X.size(); i++)
            {
                coordinates_X[i] = coordinates_X[i] * -1;
            }

            setCenter(center_X * -1, center_Y);
            setOrigin(origin_X * -1, origin_Y);
        }
    }
};

class Square : public Shape {
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do quadrado
    Square(double center_Xc, double center_Yc, double edgeLenghtc, GLFWwindow* window)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;
        shapeWindow = window;

        origin_X = center_X - edgeLenght / 2;
        origin_Y = center_Y - edgeLenght / 2;

        calculateVertices();
    }

    void calculateVertices() override
    {
        //int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));

        //glfwGetWindowSize(shapeWindow, w, h);

        coordinates_X.push_back(origin_X);
        coordinates_Y.push_back(origin_Y);

        coordinates_X.push_back(origin_X + edgeLenght);
        coordinates_Y.push_back(origin_Y);

        coordinates_X.push_back(origin_X + edgeLenght);
        coordinates_Y.push_back(origin_Y + edgeLenght);

        coordinates_X.push_back(origin_X);
        coordinates_Y.push_back(origin_Y + edgeLenght);
    }
};

class Triangle : public Shape
{
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do triângulo
    Triangle(double center_Xc, double center_Yc, double edgeLenghtc, GLFWwindow* window)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;
        shapeWindow = window;

        origin_X = center_X - edgeLenght / 2;
        origin_Y = center_Y - edgeLenght / 3;

        calculateVertices();
    }

    void calculateVertices() override
    {
        //int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));

        //glfwGetWindowSize(shapeWindow, w, h);

        double triangleHeight = sqrt(3) * edgeLenght / 2;

        coordinates_X.push_back(origin_X);
        coordinates_Y.push_back(origin_Y);

        coordinates_X.push_back(origin_X + edgeLenght);
        coordinates_Y.push_back(origin_Y);

        coordinates_X.push_back(origin_X + edgeLenght / 2);
        coordinates_Y.push_back(origin_Y + triangleHeight);
    }
};

class Hexagon : public Shape
{
public:
    // Recebe os parâmetros de entrada e calcula o ponto (vértice) de origem (ponto inferior esquerdo) do hexágono
    Hexagon(double center_Xc, double center_Yc, double edgeLenghtc, GLFWwindow* window)
    {
        center_X = center_Xc;
        center_Y = center_Yc;
        edgeLenght = edgeLenghtc;

        origin_X = center_X - edgeLenght / 2;
        origin_Y = center_Y - edgeLenght * sqrt(3) / 2;

        calculateVertices();
    }

    void calculateVertices() override
    {
        double halfEdgeLenght = edgeLenght / 2;
        double edgeHeight = sqrt(3) * halfEdgeLenght;

        coordinates_X.push_back(origin_X);
        coordinates_Y.push_back(origin_Y);

        coordinates_X.push_back(origin_X + edgeLenght);
        coordinates_Y.push_back(origin_Y);

        coordinates_X.push_back(origin_X + edgeLenght + halfEdgeLenght);
        coordinates_Y.push_back(origin_Y + edgeHeight);

        coordinates_X.push_back(origin_X + edgeLenght);
        coordinates_Y.push_back(origin_Y + edgeHeight + edgeHeight);

        coordinates_X.push_back(origin_X);
        coordinates_Y.push_back(origin_Y + edgeHeight + edgeHeight);

        coordinates_X.push_back(origin_X - halfEdgeLenght);
        coordinates_Y.push_back(origin_Y + edgeHeight);
    }
};

void drawAxis(GLFWwindow* window)
{
    // width; height
    int* w = (int*)malloc(sizeof(int)), * h = (int*)malloc(sizeof(int));
    int tickSize = 10;

    glfwGetWindowSize(window, w, h);

    if (w == NULL or h == NULL)
        return;

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
        glVertex2f((double(i) / AXIS_TICK_REFERENCE), double(-tickSize) / (*h));
        glVertex2f((double(i) / AXIS_TICK_REFERENCE), double(tickSize) / (*h));

        // Ticks eixo Y
        glVertex2f(double(-tickSize) / (*w), (double(i) / AXIS_TICK_REFERENCE));
        glVertex2f(double(tickSize) / (*w), (double(i) / AXIS_TICK_REFERENCE));
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
    glScalef((double)(800) / (double)(glutGet(GLUT_WINDOW_WIDTH)), (double)(800) / (double)(glutGet(GLUT_WINDOW_HEIGHT)), 1.0f);

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
    vector<double> x_shape;
    vector<double> y_shape;
    int control = 0, inputOption = 0, mainOption = 0, auxInput = 0;
    double auxX, auxY;
    bool isPointRepeated = false;

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
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
        glLoadIdentity(); //Reset the drawing perspective

        //////////// DRAWING ZONE ////////////

            drawAxis(window);

            for (int i = 0; i < shapes.size(); i++)
                shapes[i].drawShape();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

        //////////// END OF DRAWING ZONE ////////////

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

                // Create shape based on keyboard input points
                if (inputOption == 1)
                {
                    while (auxInput != 2)
                    {
                        isPointRepeated = false;

                        cout << "\n1 - New point" << endl;
                        cout << "2 - Stop Drawing (If less than 3 points were entered no drawing will be generated)." << endl;
                        cin >> auxInput;

                        // Adding a new poit to the shape
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

                            for (int i = 0; i < x_shape.size(); i++)
                            {
                                if (x_shape[i] == auxX and y_shape[i] == auxY)
                                {
                                    cout << "\nThis point was already entered!" << endl;
                                    isPointRepeated = true;
                                }
                            }

                            if (!isPointRepeated)
                            {
                                x_shape.push_back(auxX / AXIS_TICK_REFERENCE);
                                y_shape.push_back(auxY / AXIS_TICK_REFERENCE);
                            }
                        }
                    }

                    if (x_shape.size() < 3)
                        cout << "\nLess than 3 points entered. NO drawing will be generated!" << endl;

                    // Set center and origin of the shape and create it
                    else
                    {
                        cout << "\nType center (X and Y):" << endl;

                        cin >> auxX >> auxY;

                        while (((auxX > CANVAS_SIZE) or (auxX < -CANVAS_SIZE)) or ((auxY > CANVAS_SIZE) or (auxY < -CANVAS_SIZE))) {
                            cout << "\nCoordinates must be in the interval of -" << CANVAS_SIZE << " and " << CANVAS_SIZE << ", type X and Y again:" << endl;
                            cin >> auxX >> auxY;
                        }
                        
                        Shape sh = Shape(x_shape, y_shape);

                        sh.setCenter(auxX/AXIS_TICK_REFERENCE, auxY/AXIS_TICK_REFERENCE);
                        sh.setOrigin(x_shape[0], y_shape[0]);

                        shapes.push_back(sh);
                    }

                    x_shape.clear();
                    y_shape.clear();
                    auxInput = 0;
                }

                //If option of typing center coordinates and size was selected
                else if (inputOption == 3) {
                    int shapeOption = 0;
                    double centerX, centerY, size;

                    while (shapeOption < 1 or shapeOption > 3)
                    {
                        cout << "\nChoose Figure Type:" << endl;
                        cout << "1 - Square" << endl;
                        cout << "2 - Triangle" << endl;
                        cout << "3 - Hexagon" << endl;
                        cin >> shapeOption;
                    }

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

                    centerX = centerX / AXIS_TICK_REFERENCE;
                    centerY = centerY / AXIS_TICK_REFERENCE;
                    size = size / AXIS_TICK_REFERENCE;

                    //Call drawing methods for each option
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
                else {
                    cout << "fazer o resto kkk";
                }
            }
        }

        //shapes[0].translateShape(double(2)/AXIS_TICK_REFERENCE, double(2)/AXIS_TICK_REFERENCE);
        //shapes[0].rotateShape(-45);
        //shapes[0].scaleShape(double(0.5));
        //shapes[0].mirrorShape('y');
        //shapes[0].shearShape('x', double(-4)/AXIS_TICK_REFERENCE);
    }

    glfwTerminate();
    return 0;
}