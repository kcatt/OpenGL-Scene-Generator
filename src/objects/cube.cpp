#include "cube.h"
#include <iostream>

Cube::Cube()
{
    std::vector<Vector3> vertVec {
        Vector3(-1.0f, -1.0f, -1.0f),
        Vector3( 1.0f, -1.0f, -1.0f),
        Vector3( 1.0f,  1.0f, -1.0f),
        Vector3( 1.0f,  1.0f, -1.0f),
        Vector3(-1.0f,  1.0f, -1.0f),
        Vector3(-1.0f, -1.0f, -1.0f),

        Vector3(-1.0f, -1.0f,  1.0f),
        Vector3( 1.0f, -1.0f,  1.0f),
        Vector3( 1.0f,  1.0f,  1.0f),
        Vector3( 1.0f,  1.0f,  1.0f),
        Vector3(-1.0f,  1.0f,  1.0f),
        Vector3(-1.0f, -1.0f,  1.0f),

        Vector3(-1.0f,  1.0f,  1.0f),
        Vector3(-1.0f,  1.0f, -1.0f),
        Vector3(-1.0f, -1.0f, -1.0f),
        Vector3(-1.0f, -1.0f, -1.0f),
        Vector3(-1.0f, -1.0f,  1.0f),
        Vector3(-1.0f,  1.0f,  1.0f),

        Vector3( 1.0f,  1.0f,  1.0f),
        Vector3( 1.0f,  1.0f, -1.0f),
        Vector3( 1.0f, -1.0f, -1.0f),
        Vector3( 1.0f, -1.0f, -1.0f),
        Vector3( 1.0f, -1.0f,  1.0f),
        Vector3( 1.0f,  1.0f,  1.0f),

        Vector3(-1.0f, -1.0f, -1.0f),
        Vector3( 1.0f, -1.0f, -1.0f),
        Vector3( 1.0f, -1.0f,  1.0f),
        Vector3( 1.0f, -1.0f,  1.0f),
        Vector3(-1.0f, -1.0f,  1.0f),
        Vector3(-1.0f, -1.0f, -1.0f),

        Vector3(-1.0f,  1.0f, -1.0f),
        Vector3( 1.0f,  1.0f, -1.0f),
        Vector3( 1.0f,  1.0f,  1.0f),
        Vector3( 1.0f,  1.0f,  1.0f),
        Vector3(-1.0f,  1.0f,  1.0f),
        Vector3(-1.0f,  1.0f, -1.0f)
    };

    mesh.Create(vertVec);
    mesh.SetUpGL();
}

void Cube::Draw()
{
    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniform3f(matAmbientLoc,  material.ambient.r, material.ambient.g, material.ambient.b);
    glUniform3f(matDiffuseLoc,  material.diffuse.r, material.diffuse.g, material.diffuse.b);
    glUniform3f(matSpecularLoc, material.specular.r, material.specular.g, material.specular.b);
    glUniform3f(matEmissiveLoc, material.emissive.r, material.emissive.g, material.emissive.b);
    glUniform1f(matSpecExponentLoc, material.specularExponent);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);

    mesh.Draw();
}