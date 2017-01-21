#include "mesh.h"
#include <iterator>
#include <algorithm>
#include <iostream>

Face::Face()
{

}

Face::~Face()
{

}

Mesh::Mesh()
{
    numVerts = numFaces = numNorms = 0;
    //vertices   = NULL;
    //normals  =  NULL;
    faces    = NULL;
    mode     = MODE_SOLID; // Default is to make solid mesh
}

Mesh::Mesh(const std::string& fileName)
{
    numVerts = numFaces = numNorms = 0;
    //vertices   = NULL;
    //normals  =  NULL;
    faces    = NULL;
    mode     = MODE_SOLID; // Default is to make solid mesh
    ReadMesh(fileName);
}

Mesh::Mesh(const std::vector<Vector3>& vertexVector)
{
    vertices.resize(vertexVector.size());// = new Vector3[vertexVector.size()];
    normals.resize(vertexVector.size());// = new Vector3[vertexVector.size()];
    numVerts = vertexVector.size();
    numNorms = vertexVector.size();
    // The number of faces is the vertex vector size divided by 3 because
    // each face is one triangle, and the vertices are given in triangular form
    numFaces = vertexVector.size()/3;

    std::copy(vertexVector.begin(), vertexVector.end(), std::begin(vertices));
    
    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << vertices[i] << std::endl;
    }

    faces = new Face[numFaces];
    GenerateNormals();
    ReduceArrays();
    GenerateIndexVector();
    CreateGLArrays();
}

void Mesh::DrawEdges() const
{

}

void Mesh::DrawFaces() const
{

}

void Mesh::Draw()
{
    glBindVertexArray(meshVAO);

    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);

    glDrawElements(GL_TRIANGLES, indexVec.size(), GL_UNSIGNED_INT, 0);   
    glBindVertexArray(0);
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

void Mesh::FreeMesh()
{

}

bool Mesh::IsEmpty() const
{

}

void Mesh::MakeEmpty()
{

}

void Mesh::ReadMesh(const std::string& file)
{

}

void Mesh::SetRenderMode(RenderMode m )
{

}

void Mesh::GenerateNormals()
{
    for (int i = 0; i < numVerts; i += 3)
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
    for (size_t i = 0; i < numVerts; i++)
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
    indexVec.resize(numVerts*2);

    int index = 0;

    for (int i = 0; i < numVerts; i++)
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
