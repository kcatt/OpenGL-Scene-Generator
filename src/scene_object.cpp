#include "scene_object.h"

#include <iostream>

SceneObject::~SceneObject()
{
    if (objectVerts != NULL)
        delete[] objectVerts;
    
    /*if (mesh != NULL)
       delete mesh;*/
}

void SceneObject::Draw() { }

void SceneObject::TellMaterials()
{
    float amb[4], diff[4], spec[4], emiss[4];
    material.ambient.Build4Tuple(amb);
    material.diffuse.Build4Tuple(diff);
    material.specular.Build4Tuple(spec);
    material.emissive.Build4Tuple(emiss);
    
}

void SceneObject::SetModelMatrixLoc(GLuint location)
{
    modelMatrixLoc = location;
}