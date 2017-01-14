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

    GLFWwindow* window = glfwCreateWindow(800, 600, "Scene Description Language Generator", nullptr, nullptr);
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

    glEnable(GL_DEPTH_TEST);
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    
    glViewport(0, 0, width, height);

    Shader shader(argv[1], argv[2]);

    Sphere c;

    GLuint modelMat = glGetUniformLocation(shader.GetProgram(), "model");
    GLuint viewMat = glGetUniformLocation(shader.GetProgram(), "view");
    GLuint projectionMat = glGetUniformLocation(shader.GetProgram(), "projection");

    Camera cam(viewMat, projectionMat);
    //cam.Set(Vector3(3, 0, 0), Vector3(0, 0, 0), Vector3(0, 1, 0));

    c.SetModelMatrixLoc(modelMat);
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        glClearColor(0.2f, 0.3f, 0.3f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.Use();
        cam.UpdateMatrices();
        c.Draw();

        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}