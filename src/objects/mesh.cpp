#include "mesh.h"
#include <iterator>
#include <algorithm>
#include <iostream>

Mesh::Mesh()
{
    mode = MODE_SOLID; // Default is to make solid mesh
}

Mesh::Mesh(const std::vector<Vector3>& vertexVector)
{
    Create(vertexVector);

    mode = MODE_SOLID; // Default is to make solid mesh
}

void Mesh::Create(const std::vector<Vector3>& vertexVector, bool hardEdges)
{
    vertices.resize(vertexVector.size());
    normals.resize(vertexVector.size());

    std::copy(vertexVector.begin(), vertexVector.end(), vertices.begin());

    GenerateNormals();
    
    if (!hardEdges)
    {
        ReduceArrays();
        GenerateIndexVector();
        CreateGLArrays();
    }
    else
    {
        SetHardEdgeGLArrays();
    }
}

void Mesh::DrawGL() const
{
    glBindVertexArray(meshVAO);
    glDrawElements(GL_TRIANGLES, indexVec.size(), GL_UNSIGNED_INT, 0);   
    glBindVertexArray(0);
}

void Mesh::DrawEdges() const
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    DrawGL();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Mesh::DrawFaces() const
{
    DrawGL();
}

void Mesh::Draw()
{
    switch (mode)
    {
        case MODE_WIRE:
            DrawEdges();
            break;
        case MODE_SOLID:
            DrawFaces();
            break;
        case MODE_WIRE_SOLID:
            
            DrawFaces();
            DrawEdges();
            break;
    }
}

void Mesh::SetUpGL()
{
    glGenVertexArrays(1, &meshVAO);
    glGenBuffers(1, &meshVBO);
    glGenBuffers(1, &meshEBO);

    glBindVertexArray(meshVAO);

    glBindBuffer(GL_ARRAY_BUFFER, meshVBO);
    glBufferData(GL_ARRAY_BUFFER, reducedGLArray.size() * sizeof(GLfloat), &reducedGLArray[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexVec.size() * sizeof(GLuint), &indexVec[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::SetRenderMode(RenderMode m)
{
    mode = m;
}

void Mesh::SetGLArrays(Vector3* vertices, Vector3* normals, size_t numVerts, size_t numNorms,
                         const std::vector<int>& vertIndices, const std::vector<int>& normIndices)
{
    for (size_t i = 0; i < numVerts; i++)
    {
        reducedGLArray.push_back(vertices[i].x);
        reducedGLArray.push_back(vertices[i].y);
        reducedGLArray.push_back(vertices[i].z);

        reducedGLArray.push_back(normals[i].x);
        reducedGLArray.push_back(normals[i].y);
        reducedGLArray.push_back(normals[i].z);
    }

    indexVec.resize(vertIndices.size() * 2);

    for (size_t i = 0; i < vertIndices.size(); i++)
    {
        indexVec[i]   = vertIndices[i];
        indexVec[i+3] = normIndices[i];
    }   
}

void Mesh::SetHardEdgeGLArrays()
{
    indexVec.resize(vertices.size()*2);

    size_t index = 0;

    for (size_t i = 0; i < vertices.size(); i++)
    {
        reducedGLArray.push_back(vertices[i].x);
        reducedGLArray.push_back(vertices[i].y);
        reducedGLArray.push_back(vertices[i].z);

        reducedGLArray.push_back(normals[i].x);
        reducedGLArray.push_back(normals[i].y);
        reducedGLArray.push_back(normals[i].z);

        // The indices for the normals and the vertices are the same because OpenGL
        // views the lists of the two as their own separate lists
        indexVec[index] = i;
        indexVec[index+3] = i;

        if (((index+1) % 3) == 0 && (((index+4) % 6) == 0))
            index += 4;
        else
            index++;
    } 
}

void Mesh::GenerateNormals()
{
    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        // Calculate the face normal
        Vector3 normal = CalculateFaceNormal(vertices[i], vertices[i+1], vertices[i+2]);

        normals[i]   = normal;
        normals[i+1] = normal;
        normals[i+2] = normal;
    }
}

void Mesh::ReduceArrays()
{
    for (size_t i = 0; i < vertices.size(); i++)
    {
        auto vertPosIt = std::find(reducedVerts.begin(), reducedVerts.end(), vertices[i]);
        
        if (vertPosIt == reducedVerts.end())
        {
            reducedVerts.push_back(vertices[i]);
            reducedNorms.push_back(normals[i]);
        }
        else
        {
            size_t index = std::distance(reducedVerts.begin(), vertPosIt);
            reducedNorms[index] = reducedNorms[index] + normals[i];
        }
    }
}

void Mesh::GenerateIndexVector()
{
    indexVec.resize(vertices.size()*2);

    int index = 0;

    for (size_t i = 0; i < vertices.size(); i++)
    {
        auto vertPosIt = std::find(reducedVerts.begin(), reducedVerts.end(), vertices[i]);
        size_t vertIndex = std::distance(reducedVerts.begin(), vertPosIt);

        // The indices for the normals and the vertices are the same because OpenGL
        // views the lists of the two as their own separate lists
        indexVec[index] = vertIndex;
        indexVec[index+3] = vertIndex;

        if (((index+1) % 3) == 0 && (((index+4) % 6) == 0))
            index += 4;
        else
            index++;
    }
}

void Mesh::CreateGLArrays()
{
    for (size_t i = 0; i < reducedVerts.size(); i++)
    {
        reducedGLArray.push_back(reducedVerts[i].x);
        reducedGLArray.push_back(reducedVerts[i].y);
        reducedGLArray.push_back(reducedVerts[i].z);

        reducedGLArray.push_back(reducedNorms[i].x);
        reducedGLArray.push_back(reducedNorms[i].y);
        reducedGLArray.push_back(reducedNorms[i].z);
    }
}

Vector3 Mesh::CalculateFaceNormal(const Vector3& vert1, const Vector3& vert2, const Vector3& vert3)
{
    Vector3 line1 = vert2 - vert1;
    Vector3 line2 = vert3 - vert1;

    Vector3 normal = Vector3::Cross(line1, line2);

    // if the normal is pointing inward, invert it to be pointing outward
    if (normal.Dot(vert1 - Vector3(0, 0, 0)) < 0)
        normal.Scale(-1);
    
    if (normal.Magnitude() != 0)
        normal.Normalize();

    return normal;
}