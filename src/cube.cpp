#include "cube.h"
#include <iostream>

Cube::Cube()
{
    std::vector<Vector3> vertVec {
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

    mesh.Create(vertVec);
    mesh.SetUpGL();
}

void Cube::Draw()
{
    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);

    mesh.Draw();
}