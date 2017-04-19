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
#include "mesh.h"
#include "scene_object.h"

using namespace std;
using namespace nanogui;

float windowWidth = 1024;
float windowHeight = 768;
string autosaveName = "";
string loadName = "";

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
void MouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
void HandleMouseMovement();
void ResizeCallback(GLFWwindow* window, int width, int height);
void ParseOptions(int argc, char* argv[]);

struct MousePositionSave
{
    GLfloat lastX, lastY, currX, currY;
    bool firstPos = true;
};

struct MousePositionSave mousePosition;
Camera* cam = NULL;
GLFWwindow* window = NULL;
Screen* screen = NULL;
Scene  scene;

// Variables needed to remember state of mouse buttons being held
bool rightHeld = false;
bool middleHeld = false;

int main(int argc, char* argv[])
{
    ParseOptions(argc, argv);

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(windowWidth, windowHeight, "Scene Description Language Generator", nullptr, nullptr);
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

    Shader shader("src/vshader.glsl", "src/fshader.glsl");
    Shader boundsShader("src/vshader-bounds.glsl", "src/fshader-bounds.glsl");

    scene.SetBackground(Color3(0.1f, 0.3f, 0.1f));
    
    GLuint modelMat = glGetUniformLocation(shader.GetProgram(), "model");
    GLuint lightColor = glGetUniformLocation(shader.GetProgram(), "light.color");
    GLuint lightPos = glGetUniformLocation(shader.GetProgram(), "light.position");
    GLuint lightAmbient = glGetUniformLocation(shader.GetProgram(), "light.ambient");
    GLuint viewPos = glGetUniformLocation(shader.GetProgram(), "viewPos");
    GLuint matAmbient = glGetUniformLocation(shader.GetProgram(), "material.ambient");
    GLuint matDiffuse = glGetUniformLocation(shader.GetProgram(), "material.diffuse");
    GLuint matSpecular = glGetUniformLocation(shader.GetProgram(), "material.specular");
    GLuint matEmissive = glGetUniformLocation(shader.GetProgram(), "material.emissive");
    GLuint matSpecExponent = glGetUniformLocation(shader.GetProgram(), "material.shininess");
    GLuint modelViewMat = glGetUniformLocation(shader.GetProgram(), "modelView");
    GLuint boundsModelMat = glGetUniformLocation(boundsShader.GetProgram(), "modelView");

    scene.SetModelUniformLocations(modelMat, matAmbient, matDiffuse, matSpecular, matEmissive, matSpecExponent);
    scene.SetLightUniformLocations(lightPos, lightColor, lightAmbient);
    scene.SetModelViewUniformLocation(modelViewMat);
    scene.SetBoundsModelViewUnformLocation(boundsModelMat);

    scene.interface = new Interface(screen);
    scene.SetUpMainDialog();

    cam = new Camera();
    cam->SetShape(45.0f, width, height, 0.1f, 200.0f);
    cam->Set(Vector3(0, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

    glfwSetFramebufferSizeCallback(window,
        [](GLFWwindow *, int width, int height) {
            screen->resizeCallbackEvent(width, height);
            cam->SetShape(45.0f, width, height, 0.1f, 200.0f);
        }
    );

    scene.SetCamera(cam);

    // Load the given file if it was passed as an argument
    if (loadName != "")
	scene.ReadFile(loadName);
    
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
        cam->Notify();
        cPos = cam->GetPosition();

        glUniform3f(viewPos, cPos.x, cPos.y, cPos.z);

        scene.DrawScene();

        boundsShader.Use();
        scene.DrawSelectedBounds();

        screen->setVisible(true);
        screen->performLayout();

        screen->drawContents();
        screen->drawWidgets();

        glfwSwapBuffers(window);
    }

    //delete cam;
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
    
    // If the mouse is captured by the gui, do nothing
    if (screen->mouseButtonCallbackEvent(button, action, modifiers))
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
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        scene.ResetRenderModes();

        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        Vector3 dir = cam->MouseToWorld(xPos, yPos);

        dir = dir - cam->GetPosition();

        RayCast ray(cam->GetPosition(), dir);
        
        SceneObject* selected = ray.IntersectTest(scene.objects);

        if (selected != NULL)
            selected->mesh.SetRenderMode(Mesh::MODE_WIRE_SOLID);

        scene.SetSelectedObject(selected);
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

void ParseOptions(int argc, char* argv[])
{
    vector<string> temp;
    for (int i = 1; i < argc; i++) {
        temp.push_back(argv[i]);
    }
    for (size_t i = 0; i < temp.size(); i+=2) {
        if (temp[i] == "-w" ||
                   temp[i] == "-W") {
            if (i+1 == temp.size()) {
                cout << "Width flag set, but no block size given. Defaulting to 640." << endl;
                continue;
            }
            windowWidth = atoi(temp[i+1].c_str());
        } else if (temp[i] == "-h" ||
                   temp[i] == "-H") {
            if (i+1 == temp.size()) {
                cout << "Height flag set, but no block size given. Defaulting to 480." << endl;
                continue;
            }
            windowHeight = atoi(temp[i+1].c_str());
        } else if (temp[i] == "-f" ||
                   temp[i] == "-F") {
            if (i+1 == temp.size()) {
              cout << "File flag set, but no filename given. Defaulting to scene.txt." << endl;
              continue;
            }
            loadName = temp[i+1];
        }
	else if (temp[i] == "a" ||
		 temp[i] == "A") {
	    if (i+1 == temp.size()) {
		cout << "Autosave file flag set, but no filename given. Defaulting to auto generated name." << endl;
		continue;
	    }
	    autosaveName = temp[i+1];
	}
    }
}
