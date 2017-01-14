/**********


Triangle subdivision - http://stackoverflow.com/questions/26790422/recursive-subdivision-on-octahedron-in-opengl
Add each triangle at bottom of recursion to vector
Copy vector into another vector, removing duplicate vertices
Read through first vector, look up its index in reduced vector to create index array
using reduced vector and index array, create VBO, VAO, and EBO

**********/

#include <algorithm>
#include <iterator>
#include "sphere.h"
#include <iostream>

std::vector<GLuint>  Sphere::indexVector;
std::vector<Vector3> Sphere::vertVector;
std::vector<Vector3> Sphere::reducedVertVector;
std::vector<GLfloat> Sphere::reducedVertArray;
bool                 Sphere::sphereSetUp = false;
GLuint               Sphere::sphereVBO = 0;
GLuint               Sphere::sphereVAO = 0;
GLuint               Sphere::sphereEBO = 0;

Sphere::Sphere()
{
    if (!sphereSetUp)
        SetUpSphere();
}

void Sphere::Draw()
{
    glBindVertexArray(sphereVAO);

    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);
    
    glDrawElements(GL_TRIANGLES, indexVector.size(), GL_UNSIGNED_INT, 0);   
    
    glBindVertexArray(0);
}

void Sphere::SetUpSphere()
{
    sphereSetUp = true;

    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, -0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(-0.5f, 0, -0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, 0.5f), Vector3(-0.5f, 0, -0.5f), Vector3(0, -0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, -0.5f), Vector3(0.5f, 0, -0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(-0.5f, 0, -0.5f), Vector3(0.5f, 0, -0.5f), Vector3(0, -0.5f, 0), 4);
    SubdivideTriangles(Vector3(0.5f, 0, -0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, 0.5f, 0), 4);
    SubdivideTriangles(Vector3(0.5f, 0, -0.5f), Vector3(0.5f, 0, 0.5f), Vector3(0, -0.5f, 0), 4);
    ReduceVertexVector();
    GenerateIndexVector();
    ConvertVectorToGLArrayVector();

    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);

    glBindVertexArray(sphereVAO);

    glBindBuffer(GL_ARRAY_BUFFER, sphereVBO);
    glBufferData(GL_ARRAY_BUFFER, reducedVertArray.size() * sizeof(GLfloat), &reducedVertArray[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sphereEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexVector.size() * sizeof(GLuint), &indexVector[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Sphere::SubdivideTriangles(Vector3 vert1, Vector3 vert2, Vector3 vert3, int level)
{
    if (level == 0)
    {
        // Normalize the point so that the radius will be 0.5
        NormalizePoint(vert1, 0.5f);
        NormalizePoint(vert2, 0.5f);
        NormalizePoint(vert3, 0.5f);
        
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

void Sphere::ReduceVertexVector()
{
    for (size_t i = 0; i < vertVector.size(); i++)
    {
        if (std::find(reducedVertVector.begin(), reducedVertVector.end(), vertVector[i]) == reducedVertVector.end())
            reducedVertVector.push_back(vertVector[i]);
    }
}

void Sphere::GenerateIndexVector()
{
    for (size_t i = 0; i < vertVector.size(); i++)
    {
        auto vertPosIt = std::find(reducedVertVector.begin(), reducedVertVector.end(), vertVector[i]);
        size_t vertIndex = std::distance(reducedVertVector.begin(), vertPosIt);

        indexVector.push_back(vertIndex);
    }
}

void Sphere::ConvertVectorToGLArrayVector()
{
    for (size_t i = 0; i < reducedVertVector.size(); i++)
    {
        reducedVertArray.push_back(reducedVertVector[i].x);
        reducedVertArray.push_back(reducedVertVector[i].y);
        reducedVertArray.push_back(reducedVertVector[i].z);
    }
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