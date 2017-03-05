#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nanogui/nanogui.h>

#include <iostream>
#include <fstream>
#include <string>

#include "shader.h"
#include "camera.h"
#include "vector3.h"
#include "scene.h"
#include "ray_cast.h"

using namespace std;
using namespace nanogui;

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
void HandleMouseMovement();
void ResizeCallback(GLFWwindow* window, int width, int height);

struct MousePositionSave
{
    GLfloat lastX, lastY, currX, currY;
    bool firstPos = true;
};

struct MousePositionSave mousePosition;
Camera* cam = NULL;
GLFWwindow* window = NULL;
Screen* screen = NULL;

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
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glEnable(GL_DEPTH_TEST);

    screen = new Screen();
    screen->initialize(window, true);

    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetScrollCallback(window, ScrollCallback);
    glfwSetWindowSizeCallback(window, ResizeCallback);

    glfwSetCursorPosCallback(window,
            [](GLFWwindow *, double x, double y) {
            screen->cursorPosCallbackEvent(x, y);
        }
    );

    glfwSetKeyCallback(window,
        [](GLFWwindow *, int key, int scancode, int action, int mods) {
            screen->keyCallbackEvent(key, scancode, action, mods);
        }
    );

    glfwSetCharCallback(window,
        [](GLFWwindow *, unsigned int codepoint) {
            screen->charCallbackEvent(codepoint);
        }
    );

    glfwSetDropCallback(window,
        [](GLFWwindow *, int count, const char **filenames) {
            screen->dropCallbackEvent(count, filenames);
        }

    );

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *, int width, int height) {
            screen->resizeCallbackEvent(width, height);
        }
    );

    Shader shader(argv[1], argv[2]);
    Scene  scene;

    scene.SetBackground(Color3(0.2f, 0.3f, 0.3f));
    
    GLuint modelMat = glGetUniformLocation(shader.GetProgram(), "model");
    GLuint viewMat = glGetUniformLocation(shader.GetProgram(), "view");
    GLuint projectionMat = glGetUniformLocation(shader.GetProgram(), "projection");
    GLuint lightColor = glGetUniformLocation(shader.GetProgram(), "light.color");
    GLuint lightPos = glGetUniformLocation(shader.GetProgram(), "light.position");
    GLuint lightAmbient = glGetUniformLocation(shader.GetProgram(), "light.ambient");
    GLuint viewPos = glGetUniformLocation(shader.GetProgram(), "viewPos");
    GLuint matAmbient = glGetUniformLocation(shader.GetProgram(), "material.ambient");
    GLuint matDiffuse = glGetUniformLocation(shader.GetProgram(), "material.diffuse");
    GLuint matSpecular = glGetUniformLocation(shader.GetProgram(), "material.specular");
    GLuint matEmissive = glGetUniformLocation(shader.GetProgram(), "material.emissive");
    GLuint matSpecExponent = glGetUniformLocation(shader.GetProgram(), "material.shininess");

    scene.SetModelUniformLocations(modelMat, matAmbient, matDiffuse, matSpecular, matEmissive, matSpecExponent);
    scene.SetLightUniformLocations(lightPos, lightColor, lightAmbient);

    scene.interface = new Interface(screen);
    scene.SetUpMainDialog();

    cam = new Camera(viewMat, projectionMat);
    cam->SetShape(45.0f, 800.0f, 600.0f, 0.1f, 200.0f);
    Vector3 cPos = cam->GetPosition();
    
    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_DEPTH_TEST);

        glfwPollEvents();
        HandleMouseMovement();

        glClearColor(scene.backgroundColor.r, scene.backgroundColor.g, scene.backgroundColor.b, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        cam->UpdateMatrices();
        cPos = cam->GetPosition();

        glUniform3f(viewPos, cPos.x, cPos.y, cPos.z);

        scene.DrawScene();

        screen->setVisible(true);
        screen->performLayout();

        screen->drawContents();
        screen->drawWidgets();

        glfwSwapBuffers(window);
    }

    delete cam;
    delete screen;

    nanogui::shutdown();

    glfwTerminate();
    return 0;
}

void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    cam->Slide(0, 0, -yOffset * 0.05);

    screen->scrollCallbackEvent(xOffset, yOffset);
}

void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers)
{
    // If the camera has not been set yet, do nothing
    if (cam == NULL)
        return;
    
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
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        Vector3 dir = cam->GetPosition() - cam->MouseToWorld(xPos, yPos);

        dir = dir - cam->GetPosition();

        RayCast ray(cam->GetPosition(), dir);
    }

    screen->mouseButtonCallbackEvent(button, action, modifiers);
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
        cam->Yaw((mousePosition.currX - mousePosition.lastX) * 0.05);
        cam->Pitch((mousePosition.currY - mousePosition.lastY) * 0.05);
    }
    else if (middleHeld)
    {
        cam->Slide(-(mousePosition.currX - mousePosition.lastX) * 0.005, (mousePosition.currY - mousePosition.lastY) * 0.005, 0);
    }
}   

void ResizeCallback(GLFWwindow* window, int width, int height)
{
    
}