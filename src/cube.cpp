#include "cube.h"

#include <iostream>
GLuint Cube::indexArr[36] = {
    0, 1, 2, // front face
    2, 3, 1,
    4, 5, 6,
    6, 7, 4,
    7, 3, 0,
    0, 4, 7,
    6, 2, 1,
    1, 5, 6,
    0, 1, 5,
    5, 4, 0,
    3, 2, 6,
    6, 7, 3
};

bool    Cube::cubeSetUp = false;
GLuint  Cube::cubeVBO = 0;
GLuint  Cube::cubeVAO = 0;
GLuint  Cube::cubeEBO = 0;

Cube::Cube()
{
    //define the 8 vertices that make up a cube
    objectVerts = new GLfloat[24] {
        -0.5f, -0.5f, -0.5f, // front bottom left  0
         0.5f, -0.5f, -0.5f, // front bottom right 1
         0.5f,  0.5f, -0.5f, // front top right    2
        -0.5f,  0.5f, -0.5f, // front top left     3
        -0.5f, -0.5f, 0.5f, // back bottom left   4
         0.5f, -0.5f, 0.5f, // back bottom right  5
         0.5f,  0.5f, 0.5f, // back top right     6
        -0.5f,  0.5f, 0.5f  // back top left      7
    };

    std::vector<Vector3> vec {
        Vector3(-0.5f, -0.5f, -0.5f),
        Vector3( 0.5f, -0.5f, -0.5f),
        Vector3( 0.5f,  0.5f, -0.5f),
        Vector3( 0.5f,  0.5f, -0.5f),
        Vector3(-0.5f,  0.5f, -0.5f),
        Vector3(-0.5f, -0.5f, -0.5f),

        Vector3(-0.5f, -0.5f,  0.5f),
        Vector3( 0.5f, -0.5f,  0.5f),
        Vector3( 0.5f,  0.5f,  0.5f),
        Vector3( 0.5f,  0.5f,  0.5f),
        Vector3(-0.5f,  0.5f,  0.5f),
        Vector3(-0.5f, -0.5f,  0.5f),

        Vector3(-0.5f,  0.5f,  0.5f),
        Vector3(-0.5f,  0.5f, -0.5f),
        Vector3(-0.5f, -0.5f, -0.5f),
        Vector3(-0.5f, -0.5f, -0.5f),
        Vector3(-0.5f, -0.5f,  0.5f),
        Vector3(-0.5f,  0.5f,  0.5f),

        Vector3( 0.5f,  0.5f,  0.5f),
        Vector3( 0.5f,  0.5f, -0.5f),
        Vector3( 0.5f, -0.5f, -0.5f),
        Vector3( 0.5f, -0.5f, -0.5f),
        Vector3( 0.5f, -0.5f,  0.5f),
        Vector3( 0.5f,  0.5f,  0.5f),

        Vector3(-0.5f, -0.5f, -0.5f),
        Vector3( 0.5f, -0.5f, -0.5f),
        Vector3( 0.5f, -0.5f,  0.5f),
        Vector3( 0.5f, -0.5f,  0.5f),
        Vector3(-0.5f, -0.5f,  0.5f),
        Vector3(-0.5f, -0.5f, -0.5f),

        Vector3(-0.5f,  0.5f, -0.5f),
        Vector3( 0.5f,  0.5f, -0.5f),
        Vector3( 0.5f,  0.5f,  0.5f),
        Vector3( 0.5f,  0.5f,  0.5f),
        Vector3(-0.5f,  0.5f,  0.5f),
        Vector3(-0.5f,  0.5f, -0.5f)
    };

    m = new Mesh(vec);
    m->SetUpGL();
    m->SetModelMatrixLoc(modelMatrixLoc);
    //if (!cubeSetUp)
    //    SetUpCube();
}

void Cube::Draw()
{
    m->Draw();
    /*glBindVertexArray(cubeVAO);

    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);   
    glBindVertexArray(0);*/
}


void Cube::SetUpCube()
{
    std::cout << "SETTING UP CUBE" << std::endl;

    cubeSetUp = true;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(GLfloat), objectVerts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArr), indexArr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}