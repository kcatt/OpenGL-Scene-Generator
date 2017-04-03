#include "scene_object.h"

#include <iostream>

void SceneObject::Draw() { }

void SceneObject::TellMaterials()
{
    float amb[4], diff[4], spec[4], emiss[4];
    material.ambient.Build4Tuple(amb);
    material.diffuse.Build4Tuple(diff);
    material.specular.Build4Tuple(spec);
    material.emissive.Build4Tuple(emiss);
    
}

void SceneObject::SetUniformLocations(GLuint model, GLuint ambient, GLuint diffuse, GLuint specular, GLuint emissive, GLuint specExponent)
{
    modelMatrixLoc = model;
    matAmbientLoc = ambient;
    matDiffuseLoc = diffuse;
    matSpecularLoc = specular;
    matEmissiveLoc = emissive;
    matSpecExponentLoc = specExponent;
}

void SceneObject::SetModelViewUniformLocation(GLuint modelView)
{
    modelViewMatrixLoc = modelView;
}

void SceneObject::SetBoundsModelViewUnformLocation(GLuint modelView)
{
    boundsModelViewMatrixLoc = modelView;
}

void SceneObject::Update(Camera* observable)
{
    modelViewMatrix = observable->projectionMatrix * observable->viewMatrix * transform.affine;
}

void SceneObject::DrawBounds()
{
    GLfloat modelViewMat[16];
    modelViewMatrix.ConvertToOpenGLMatrix(modelViewMat);

    glUniformMatrix4fv(boundsModelViewMatrixLoc, 1, GL_FALSE, modelViewMat);

    boundBox->mesh.Draw();
}