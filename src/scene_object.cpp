#include "scene_object.h"

#include <iostream>

SceneObject::~SceneObject()
{
    if (objectVerts != NULL)
        delete[] objectVerts;
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

Vector3 SceneObject::CalculateFaceNormal(const Vector3& vert1, const Vector3& vert2, const Vector3& vert3)
{
    Vector3 line1 = vert2 - vert1;
    Vector3 line2 = vert3 - vert1;

    Vector3 normal = Vector3::Cross(line1, line2);

    // if the normal is pointing inward, invert it to be pointing outward
    if (normal.Dot(vert1 - Vector3(0, 0, 0)) < 0)
        normal.Scale(-1);
    
    normal.Normalize();

    return normal;
}