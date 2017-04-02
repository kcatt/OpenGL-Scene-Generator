#include "mesh_3vn.h"
#include <fstream>
#include <cassert>

Mesh3VN::Mesh3VN()
{
    numVerts = 0;
    numFaces = 0;
    numNorms = 0;
    points   = NULL;
    normals  = NULL;
    lastVertUsed = -1;
    lastNormUsed = -1;
    lastFaceUsed = -1;
}

Mesh3VN::Mesh3VN(const std::string & file)
{
    Mesh3VN();
    ReadMesh(file);

    type = "mesh " + file;
}

void Mesh3VN::Draw()
{
    GLfloat modelMatrix[16];
    transform.affine.ConvertToOpenGLMatrix(modelMatrix);

    glUniform3f(matAmbientLoc,  material.ambient.r, material.ambient.g, material.ambient.b);
    glUniform3f(matDiffuseLoc,  material.diffuse.r, material.diffuse.g, material.diffuse.b);
    glUniform3f(matSpecularLoc, material.specular.r, material.specular.g, material.specular.b);
    glUniform3f(matEmissiveLoc, material.emissive.r, material.emissive.g, material.emissive.b);
    glUniform1f(matSpecExponentLoc, material.specularExponent);

    GLfloat modelViewMat[16];
    modelViewMatrix.ConvertToOpenGLMatrix(modelViewMat);

    glUniformMatrix4fv(modelMatrixLoc, 1, GL_FALSE, modelMatrix);
    glUniformMatrix4fv(modelViewMatrixLoc, 1, GL_FALSE, modelViewMat);

    mesh.Draw();
}

Mesh3VN::~Mesh3VN()
{
    Free();
}

void Mesh3VN::Free()
{
    delete [] points; // release whole vertex list
    delete [] normals;

    if (boundBox != NULL)
        delete boundBox;
}

bool Mesh3VN::IsEmpty()
{
    return (numVerts == 0) || (numFaces == 0) || (numNorms == 0);
}

void Mesh3VN::MakeEmpty()
{
    numVerts = numFaces = numNorms = 0;
}

void Mesh3VN::ReadMesh(const std::string & file)
{
    fileName = file;

    std::ifstream input;
    input.open(file.c_str());

    if (input.fail ()) {
        std::cerr << "readMesh: File " << file<< " could not be opened." << std::endl;
        exit (1);
    }

    input >> numVerts >> numNorms >> numFaces;

    points = new Vector3[numVerts];
    assert (points != NULL);
    normals = new Vector3[numNorms];
    assert (normals != NULL);

    for (size_t i = 0; i < numVerts; i++)
        input >> points[i].x >> points[i].y >> points[i].z;
    for (size_t i = 0; i < numNorms; i++)
        input >> normals[i].x >> normals[i].y >> normals[i].z;
    for (size_t i = 0; i < numFaces; i++) {
        int numFaceVerts = 0;
        input >> numFaceVerts;

        if (numFaceVerts == 4)
        {
            int vertIndices[4];
            int normIndices[4];

            Face newFace1;
            Face newFace2;

            input >> vertIndices[0] >> vertIndices[1] >> vertIndices[2] >> vertIndices[3];
            input >> normIndices[0] >> normIndices[1] >> normIndices[2] >> normIndices[3];

            newFace1.vert[0].vertIndex = vertIndices[0];
            newFace1.vert[1].vertIndex = vertIndices[1];
            newFace1.vert[2].vertIndex = vertIndices[2];
            newFace1.vert[0].normIndex = normIndices[0];
            newFace1.vert[1].normIndex = normIndices[1];
            newFace1.vert[2].normIndex = normIndices[2];

            faces.push_back(newFace1);

            newFace2.vert[0].vertIndex = vertIndices[2];
            newFace2.vert[1].vertIndex = vertIndices[3];
            newFace2.vert[2].vertIndex = vertIndices[0];
            newFace2.vert[0].normIndex = normIndices[2];
            newFace2.vert[1].normIndex = normIndices[3];
            newFace2.vert[2].normIndex = normIndices[0];

            faces.push_back(newFace2);
        }
        else
        {
            Face newFace;

            for (int j = 0; j < 3; j++)
                input >> newFace.vert[j].vertIndex;
            for (int j = 0; j < 3; j++)
                input >> newFace.vert[j].normIndex;

            faces.push_back(newFace);
        }
    }

    input.close();

    std::vector<Vector3> vertVec(points, points + numVerts);
    boundBox = new AABB(vertVec);
    boundBox->transform = &transform;

    SetUpMesh();
}

void Mesh3VN::SetUpMesh()
{
    std::vector<int> vertIndices;
    std::vector<int> normIndices;

    for (size_t i = 0; i < faces.size(); i++)
    {
        vertIndices.push_back(faces[i].vert[0].vertIndex);
        vertIndices.push_back(faces[i].vert[1].vertIndex);
        vertIndices.push_back(faces[i].vert[2].vertIndex);

        normIndices.push_back(faces[i].vert[0].normIndex);
        normIndices.push_back(faces[i].vert[1].normIndex);
        normIndices.push_back(faces[i].vert[2].normIndex);
    }

    mesh.SetGLArrays(points, normals, numVerts, numNorms, vertIndices, normIndices);
    mesh.SetUpGL();
}
