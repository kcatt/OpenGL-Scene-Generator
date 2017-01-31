#include <algorithm>
#include <iterator>
#include "sphere.h"
#include <iostream>

Sphere::Sphere()
{
    SetUpSphere();

    type = "sphere";
}

void Sphere::Draw()
{
    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);

    glUniform3f(matAmbientLoc,  material.ambient.r, material.ambient.g, material.ambient.b);
    glUniform3f(matDiffuseLoc,  material.diffuse.r, material.diffuse.g, material.diffuse.b);
    glUniform3f(matSpecularLoc, material.specular.r, material.specular.g, material.specular.b);
    glUniform3f(matEmissiveLoc, material.emissive.r, material.emissive.g, material.emissive.b);
    glUniform1f(matSpecExponentLoc, material.specularExponent);

    mesh.Draw();
}

void Sphere::SetUpSphere()
{
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, -0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(-0.5f, 0, -0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(-0.5f, 0, -0.5f), Vector3(0, -0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, -0.5f), Vector3(0.5f, 0, -0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, -0.5f), Vector3(0.5f, 0, -0.5f), Vector3(0, -0.5f, 0), 4);
    SubdivideTriangles(Vector3(0.5f, 0, -0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(0.5f, 0, -0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, -0.5f, 0), 4);
    
    mesh.Create(vertVector);
    mesh.SetUpGL();
}

void Sphere::SubdivideTriangles(Vector3 vert1, Vector3 vert2, Vector3 vert3, int level)
{
    if (level == 0)
    {
        // Normalize the point so that the radius will be 1.0
        NormalizePoint(vert1, 1.0f);
        NormalizePoint(vert2, 1.0f);
        NormalizePoint(vert3, 1.0f);
        
        vertVector.push_back(vert1);
        vertVector.push_back(vert2);
        vertVector.push_back(vert3);

        return;
    }

    Vector3 vert12;
    Vector3 vert13;
    Vector3 vert23;

    vert12 = 0.5f * (vert1 + vert2);
    vert13 = 0.5f * (vert1 + vert3);
    vert23 = 0.5f * (vert2 + vert3);

    SubdivideTriangles(vert1, vert12, vert13, level-1);
    SubdivideTriangles(vert12, vert2, vert23, level-1); 
    SubdivideTriangles(vert13, vert23, vert3, level-1);
    SubdivideTriangles(vert12, vert23, vert13, level-1);
}

void Sphere::NormalizePoint(Vector3& point, GLfloat length)
{
    Vector3 dist = point - Vector3(0, 0, 0);

    GLfloat distance = sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);

    dist.x = dist.x * (length / distance);
    dist.y = dist.y * (length / distance);
    dist.z = dist.z * (length / distance);

    point = dist;
}