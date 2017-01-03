#include "cube.h"

GLfloat Cube::indexArr[36] = {
    0, 1, 2, // front face
    0, 2, 3,
    4, 0, 3, // left face
    4, 3, 7,
    4, 5, 6, // back face
    4, 6, 7,
    1, 5, 6, // right face
    1, 6, 2,
    3, 2, 6, // top face
    3, 6, 7,
    4, 5, 1, // bottome face
    4, 1, 0
};

Cube::Cube()
{
    //define the 8 vertices that make up a cube
    objectVerts = new GLfloat[24] {
        -1.0f, -1.0f,  1.0f, // front bottom left  0
         1.0f, -1.0f,  1.0f, // front bottom right 1
         1.0f,  1.0f,  1.0f, // front top right    2
        -1.0f,  1.0f,  1.0f, // front top left     3
        -1.0f, -1.0f, -1.0f, // back bottom left   4
         1.0f, -1.0f, -1.0f, // back bottom right  5
         1.0f,  1.0f, -1.0f, // back top right     6
        -1.0f,  1.0f, -1.0f  // back top left      7
    };
}

void Cube::Draw()
{
    glBufferData(GL_ARRAY_BUFFER, sizeof(objVerts), objVerts, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENET_ARRAY_BUFFER, sizeof(indexArr), indexArr, GL_STATIC_DRAW);
}