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

}

void Sphere::SetUpSphere()
{
    //SubdivideTriangles(
}

void Sphere::SubdivideTriangles(Vector3 vert1, Vector3 vert2, Vector3 vert3, int level)
{
    if (level == 0)
    {
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

    vert12.Normalize();
    vert13.Normalize();
    vert23.Normalize();

    SubdivideTriangles(vert1, vert12, vert13, level-1);
    SubdivideTriangles(vert12, vert2, vert23, level-1); 
    SubdivideTriangles(vert12, vert23, vert13, level-1);
}

void Sphere::ReduceVertexVector()
{
    for (size_t i = 0; i < vertVector.size(); i++)
    {
        if (std::find(reducedVertVector.begin(), reducedVertVector.end(), vertVector[i]) != reducedVertVector.end())
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

void Sphere::ConvertVectorToGLArray()
{
    for (size_t i = 0; i < reducedVertVector.size(); i++)
    {
        reducedVertArray.push_back(reducedVertVector[i].x);
        reducedVertArray.push_back(reducedVertVector[i].y);
        reducedVertArray.push_back(reducedVertVector[i].z);
    }
}