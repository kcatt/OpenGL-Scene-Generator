#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

#include "shader.h"
#include "sphere.h"
#include "camera.h"
#include "vector3.h"

using namespace std;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
void HandleMouseMovement();

struct MousePositionSave
{
    GLfloat lastX, lastY, currX, currY;
    bool firstPos = true;
};

struct MousePositionSave mousePosition;
Camera* cam = NULL;
GLFWwindow* window = NULL;

// Variables needed to remember state of mouse buttons being held
bool rightHeld = false;
bool middleHeld = false;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Incorrect number of arguments!" << endl;
        cout << "Usage: [executable] vertexShader fragmentShader" << endl;
        return -1;
    }

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(800, 600, "Scene Description Language Generator", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create the GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    //glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    Shader shader(argv[1], argv[2]);

    Sphere c;

    GLuint modelMat = glGetUniformLocation(shader.GetProgram(), "model");
    GLuint viewMat = glGetUniformLocation(shader.GetProgram(), "view");
    GLuint projectionMat = glGetUniformLocation(shader.GetProgram(), "projection");

    cam = new Camera(viewMat, projectionMat);
    //cam.Set(Vector3(3, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));

    c.SetModelMatrixLoc(modelMat);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        HandleMouseMovement();

        glClearColor(0.2f, 0.3f, 0.3f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        cam->UpdateMatrices();
        c.Draw();

        glfwSwapBuffers(window);
    }

    delete cam;
    glfwTerminate();
    return 0;
}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    if (mousePosition.firstPos)
    {
        mousePosition.lastX = mousePosition.currX = xPos;
        mousePosition.lastY = mousePosition.currY = yPos;

        mousePosition.firstPos = false;
    }
    else
    {
        mousePosition.lastX = mousePosition.currX;
        mousePosition.lastY = mousePosition.currY;

        mousePosition.currX = xPos;
        mousePosition.currY = yPos;
    }
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    cam->Slide(0, 0, -yOffset * 0.05);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
{
    // If the camera has not been set yet, do nothing
    if (cam == NULL)
        return;

    std::cout << "RIGHT HELD: " << rightHeld << std::endl;
    
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
            rightHeld = true;
        else if (action == GLFW_RELEASE)
            rightHeld = false;
    }
    else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {   
        if (action == GLFW_PRESS)
            middleHeld = true;
        else if (action == GLFW_RELEASE)
            middleHeld = false;
    }
}

void HandleMouseMovement()
{
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    if (mousePosition.firstPos)
    {
        mousePosition.lastX = mousePosition.currX = xPos;
        mousePosition.lastY = mousePosition.currY = yPos;

        mousePosition.firstPos = false;
    }
    else
    {
        mousePosition.lastX = mousePosition.currX;
        mousePosition.lastY = mousePosition.currY;

        mousePosition.currX = xPos;
        mousePosition.currY = yPos;
    }

    if (rightHeld)
    {
        cam->Yaw(-(mousePosition.currX - mousePosition.lastX) * 0.05);
        cam->Pitch(-(mousePosition.currY - mousePosition.lastY) * 0.05);
    }
    else if (middleHeld)
    {
        cout << mousePosition.currX - mousePosition.lastX  << " " << mousePosition.currY - mousePosition.lastY<< endl;
        cam->Slide(-(mousePosition.currX - mousePosition.lastX) * 0.005, (mousePosition.currY - mousePosition.lastY) * 0.005, 0);
    }
}   