#include <cmath>
#include <iostream>
#include "tapered_cylinder.h"
#include "material.h"

#define PI 3.14159

TaperedCylinder::TaperedCylinder()
{
    topRadius = 1.0f;
    generated = false;
    type = "taperedCylinder 1";
}

void TaperedCylinder::Draw()
{
    if (!generated)
    {
        Generate();
    }

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

void TaperedCylinder::SetTopRadius(GLfloat radius)
{
    if (radius < 0)
    {
        std::cerr << "Negative radius for taperedCylinder is not valid. Using 0 as radius." << std::endl;
        radius = 0;
    }
    
    // If the radius is set to zero, set it to an indistinguishably small number to 
    // allow for proper lighting
    topRadius = (radius == 0 ? 0.0001f : radius);

    type = "taperedCylinder " + std::to_string(radius); 
}

void TaperedCylinder::Generate()
{
    generated = true;

    GenerateBase();
    GenerateTop();
    GenerateSides();
    GenerateCompleteMesh();

    mesh.Create(vertVector);
    mesh.SetUpGL();
}

void TaperedCylinder::GenerateBase()
{
    for (int i = 0; i < 360; i++)
    {
        Vector3 nextPoint(sin(i * PI/180), cos(i * PI/180), -0.5f);
        baseRing.push_back(nextPoint);
    }

    size_t secondInd = 0;

    for (int i = 0; i < 360; i++)
    {
        // The second index is the adjacent vertice that is part of the triangle
        // and is (mod 360) so the vertex at 359 can connect to the vertex at 0
        secondInd = (i+1)%360;

        baseVector.push_back(baseRing[i]);
        baseVector.push_back(baseRing[secondInd]);
        baseVector.push_back(Vector3(0, 0, -0.5f));
    }
}

void TaperedCylinder::GenerateTop()
{
    if (topRadius == 0)
    {
        topRing.push_back(Vector3(0, 0, 0.5f));
        topVector.push_back(topRing[0]);
        return;
    }

    for (int i = 0; i < 360; i++)
    {
        if (topRadius != 0)
        {
            Vector3 nextPoint(topRadius * sin(i * PI/180), topRadius * cos(i * PI/180), 0.5f);
            topRing.push_back(nextPoint);
        }
        else
        {
            topRing.push_back(Vector3(0, 0, 0.5f));
        }
    }

    size_t secondInd = 0;

    for (int i = 0; i < 360; i++)
    {
        // The second index is the adjacent vertice that is part of the triangle
        // and is (mod 360) so the vertex at 359 can connect to the vertex at 0
        secondInd = (i+1)%360;

        topVector.push_back(topRing[i]);
        topVector.push_back(topRing[secondInd]);
        topVector.push_back(Vector3(0, 0, 0.5f));
    }
}

void TaperedCylinder::GenerateSides()
{
    size_t secondInd = 0;

    for (size_t i = 0; i < 360; i++)
    {
        // The second index is the adjacent vertice that is part of the triangle
        // and is (mod 360) so the vertex at 359 can connect to the vertex at 0
        secondInd = (i+1)%360;

        /* The triangles are made as follows:
         *                   v4--v3
         *                   |  / |
         *                   | /  |
         *                   |/   |
         *                   v1--v2
         *  Vertices 3 and 1 are duplicated while being placed in the 
         *  vector, but that is reduced when the vector is pushed to the mesh */
        sideVector.push_back(baseRing[i]);
        sideVector.push_back(baseRing[secondInd]);

        // If the topRadius == 0
        if (topRadius == 0)
        {
            sideVector.push_back(topRing[0]);
            sideVector.push_back(topRing[0]);
            sideVector.push_back(topRing[0]);
        }
        else
        {
            sideVector.push_back(topRing[secondInd]);
            sideVector.push_back(topRing[secondInd]);
            sideVector.push_back(topRing[i]);
        }
        
        sideVector.push_back(baseRing[i]);
    }
}

void TaperedCylinder::GenerateCompleteMesh()
{
    for (size_t i = 0; i < baseVector.size(); i++)
    {
        vertVector.push_back(baseVector[i]);
    }

    for (size_t i = 0; i < sideVector.size(); i++)
    {
        vertVector.push_back(sideVector[i]);
    }

    if (topRadius == 0)
        return;

    for (size_t i = 0; i < topVector.size(); i++)
    {
        vertVector.push_back(topVector[i]);
    }
}