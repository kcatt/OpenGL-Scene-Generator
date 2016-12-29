#include "transform.h"
#include <cmath>

std::ostream& operator<<(std::ostream& out, const Transform& t)
{
    out << "scale " << t.scale << " rotate " << t.rotation << " translate " << t.position;
    return out;
}

Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
    this->position = position;   
    this->rotaiton = rotation;
    this->scale = scale;
}

Trasnform::Transform(const Transform& transform)
{
    Transform(transform.position, transform.rotation, transform.scale);
}

void Transform::Translate(const Vector3& translation)
{
    Translate(translation.x, translation.y, translation.z);
}

void Transform::Translate(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;

    ApplyTransform();
}

void Transform::Rotate(const Vector3& rotation)
{
    Rotate(rotation.x, rotation.y, rotation.z);
}

void Transform::Rotate(float x, float y, float z)
{
    rotation.x += x;
    rotation.y += y;
    rotation.z += z;

    CheckRotation();
    ApplyTransform();
}

void Transform::Scale(const Vector3& scale)
{
    Scale(scale.x, scale.y, scale.z);
}

void Transform::Scale(float x, float y, flaot z)
{
    scale.x += x;
    scale.y += y;
    scale.z += z;
}

void Transform::SetPosition(const Vector3& position)
{
    SetPosition(position.x, position.y, position.z);
}

void Transform::SetPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;

    ApplyTransform();
}

void Transform::SetRotation(const Vector3& rotation)
{
    SetRotation(rotation.x, rotation.y, rotation.z);
}

void Transform::SetRotation(float x, float y, float z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;

    CheckRotation();
    ApplyTransform();
}

void Transform::SetScale(const Vector3& scale)
{
    SetScale(scale.x, scale.y, scale.z);
}

void Transform::SetScale(float x, float y, float z)
{
    scale.x = x;
    scale.y = y;
    scale.z = z;

    ApplyTransform();
}

void Transform::Rotate(float angle, const Vector3& axis)
{
    Mat4x4 rm;
    Mat4x4 invRm;
    axis.Normalize();
    float radians = angle * 3.14159/180;
    float c = cos(radians);
    float s = sin(radians);
    float cMin = 1.0 - c;

    rm.matrix[0][0] = c + cMin*pow(axis.x, 2);
    rm.matrix[0][1] = cMin*axis.y*axis.x - s*axis.z;
    rm.matrix[0][2] = cMin*axis.z*axis.x + s*axis.y;
    rm.matrix[1][0] = cMin*axis.x*axis.y + s*axis.z;
    rm.matrix[1][1] = c + cMin*pow(axis.y, 2);
    rm.matrix[1][2] = cMin*axis.z*axis.y - s*axis.x;
    rm.matrix[2][0] = cMin*axis.x*axis.z - s*axis.y;
    rm.matrix[2][1] = cMin*axis.y*axis.z + s*axis.x;
    rm.matrix[2][2] = c + cMin*pow(axis.z, 2);

    invRm.matrix[0][0] = c + cMin*pow(axis.x, 2);
    invRm.matrix[0][1] = cMin*axis.y*axis.x + s*axis.z;
    invRm.matrix[0][2] = cMin*axis.z*axis.x - s*axis.y;
    invRm.matrix[1][0] = cMin*axis.x*axis.y - s*axis.z;
    invRm.matrix[1][1] = c + cMin*pow(axis.y, 2);
    invRm.matrix[1][2] = cMin*axis.z*axis.y + s*axis.x;
    invRm.matrix[2][0] = cMin*axis.x*axis.z + s*axis.y;
    invRm.matrix[2][1] = cMin*axis.y*axis.z - s*axis.x;
    invRm.matrix[2][2] = c + cMin*pow(axis.z, 2);

    rotationMat.PreMultiply(rm);
    invRotation.PostMultiply(invRm);    
}

void Transform::ApplyTransform()
{
    ResetRotationMatrices();

    Vector3 xAxis(1, 0, 0);
    Vector3 yAxis(0, 1, 0);
    Vector3 zAxis(0, 0, 1);
    Rotate(rotation.x, xAxis);
    Rotate(rotation.y, yAxis);
    Rotate(rotation.z, zAxis);

    affine.PreMultiply(rotationMat);
    invAffine.PostMultiply(invRotation);

    Mat4x4 translate;
    Mat4x4 invTrans;
    translate.matrix[0][3] = position.x;
    translate.matrix[1][3] = position.y;
    translate.matrix[2][3] = position.z;

    invTrans.matrix[0][3] = -position.x;
    invTrans.matrix[1][3] = -position.y;
    invTrans.matrix[2][3] = -position.z;

    affine.PreMultiply(translate);
    invAffine.PostMultiply(invTrans);

    Mat4x4 scaleMat;
    Mat4x4 invScale;
    
    const float sEps = 0.00001;
    
    scaleMat.matrix[0][0] = scale.x;
    scaleMat.matrix[1][1] = scale.y;
    scaleMat.matrix[2][2] = scale.z;

    if(fabs(scale.x) < sEps || fabs(scale.z) < sEps || fabs(scale.z) < sEps) {
        cerr << "Degenerate scaling transformation!\n";
    }

    invScale.matrix[0][0] = 1/scale.x;
    invScale.matrix[1][1] = 1/scale.y;
    invScale.matrix[2][2] = 1/scale.z;

    affine.PreMultiply(scaleMat);
    invAffine.PostMultiply(invScale);
}

void Transform::CheckRotation()
{
    if (rotation.x >= 360)
        rotation.x = rotation.x - 360;
    else if (rotation.x <= -360)
        rotation.x = rotation.x + 360;

    if (rotation.y >= 360)
        rotation.y = rotation.y - 360;
    else if (rotation.y <= -360)
        rotation.y = rotation.y + 360;

    if (rotation.z >= 360)
        rotation.z = rotation.z - 360;
    else if (rotation.z <= -360)
        rotation.z = rotation.z + 360;
}

void Transform::ResetRotationMatrices()
{
    rotationMat.SetIdentity();
    invRotation.SetIdentity();
}