#include <cmath>
#include "camera.h"
#include <iostream>

Camera::Camera()
{
    eye.Set(0, 0, 0);
    look.Set(0, 0, 0);
    right.Set(0, 0, 0);
    backward.Set(0, 0, 0);
    up.Set(0, 0, 0);
    viewAngle = 0;
    aspect = 0;
    nearDist = 0;
    farDist = 0;
    updateViewMatrix = false;
    updateProjectionMatrix = false;
}

void Camera::Set(Vector3 eye, Vector3 look, Vector3 up)
{
    this->eye.Set(eye);
    this->look.Set(look);

    backward.Set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
    backward.Normalize();
    right.Set(Vector3::Cross(up, backward));
    right.Normalize();
    this->up.Set(Vector3::Cross(backward, right));

    updateViewMatrix = true;
}

void Camera::SetFromAxes(Vector3 backward, Vector3 right, Vector3 up, Vector3 eye)
{
    this->eye.Set(eye);
    this->backward.Set(backward);
    this->right.Set(right);
    this->up.Set(up);

    updateViewMatrix = true;
}

/* Rotate the camera about the Z-axis */
void Camera::Roll(GLfloat angle)
{
    GLfloat c = cos(3.14159/180 * angle);
    GLfloat s = sin(3.14159/180 * angle);

    Vector3 temp(right);

    right.Set(c*temp.x - s*up.x, c*temp.y - s*up.y, c*temp.z - s*up.z);
    up.Set(s*temp.x + c*up.x, s*temp.y + c*up.y, s*temp.z + c*up.z);

    updateViewMatrix = true;
}

/* Rotate the camera about the X-axis */
void Camera::Pitch(GLfloat angle)
{
    GLfloat c = cos(3.14159/180 * angle);
    GLfloat s = sin(3.14158/180 * angle);
    
    Vector3 temp(up);

    up.Set(c*temp.x - s*backward.x, c*temp.y - s*backward.y, c*temp.z - s*backward.z);
    backward.Set(s*temp.x + c*backward.x, s*temp.y + c*backward.y, s*temp.z + c*backward.z);
    updateViewMatrix = true;
}

/* Rotate the camera about the Y-axis */
void Camera::Yaw(GLfloat angle)
{
    GLfloat c = cos (3.14159/180 * angle);
    GLfloat s = sin (3.14159/180 * angle);

    Vector3 temp(backward);

    backward.Set(c*temp.x - s*right.x, c*temp.y - s*right.y, c*temp.z - s*right.z);
    right.Set(s*temp.x + c*right.x, s*temp.y + c*right.y, s*temp.z + c*right.z);

    updateViewMatrix = true;
}

/* Function to translate the camera in a direction
 * Params: delU - Change in x direction,
           delV - Change in y direction,
           delN - Change in z direction */
void Camera::Slide(GLfloat delU, GLfloat delV, GLfloat delN)
{
    GLfloat delX = delU*right.x + delV*up.x + delN*backward.x;
    GLfloat delY = delU*right.y + delV*up.y + delN*backward.y;
    GLfloat delZ = delU*right.z + delV*up.z + delN*backward.z;
    eye.Set(eye.x+delX, eye.y+delY, eye.z+delZ);
    
    updateViewMatrix = true;
}

void Camera::SetShape(GLfloat viewAngle, GLint width, GLint height, GLfloat nearDist, GLfloat farDist)
{
    this->viewAngle = viewAngle;
    this->width     = width;
    this->height    = height;
    this->aspect    = (GLfloat)width/(GLfloat)height;
    this->nearDist  = nearDist;
    this->farDist   = farDist;

    updateProjectionMatrix = true;
}

void Camera::GetShape(GLfloat& viewAngle, GLfloat& aspect, GLfloat& nearDist, GLfloat& farDist)
{
    viewAngle = this->viewAngle;
    aspect    = this->aspect;
    nearDist  = this->nearDist;
    farDist   = this->farDist;
}

void Camera::GetShape(GLfloat& viewAngle, GLfloat& width, GLfloat& height, GLfloat& nearDist, GLfloat& farDist)
{
    viewAngle = this->viewAngle;
    width     = this->width;
    height    = this->height;
    nearDist  = this->nearDist;
    farDist   = this->farDist;
}

void Camera::SetViewMatrix()
{
    viewMatrix.matrix[0][0] = right.x;
    viewMatrix.matrix[0][1] = right.y;
    viewMatrix.matrix[0][2] = right.z;
    viewMatrix.matrix[0][3] = (-1 * eye).Dot(right);
    viewMatrix.matrix[1][0] = up.x;
    viewMatrix.matrix[1][1] = up.y;
    viewMatrix.matrix[1][2] = up.z;
    viewMatrix.matrix[1][3] = (-1 * eye).Dot(up);
    viewMatrix.matrix[2][0] = backward.x;
    viewMatrix.matrix[2][1] = backward.y;
    viewMatrix.matrix[2][2] = backward.z;
    viewMatrix.matrix[2][3] = (-1 * eye).Dot(backward);
    viewMatrix.matrix[3][0] = 0;
    viewMatrix.matrix[3][1] = 0;
    viewMatrix.matrix[3][2] = 0;
    viewMatrix.matrix[3][3] = 1;

    invViewMatrix.Set(viewMatrix.Transpose());
    invViewMatrix.matrix[0][3] = 0;
    invViewMatrix.matrix[1][3] = 0;
    invViewMatrix.matrix[2][3] = 0;
    invViewMatrix.matrix[3][3] = 1;

    invViewMatrix.matrix[3][0] = 0;
    invViewMatrix.matrix[3][1] = 0;
    invViewMatrix.matrix[3][2] = 0;

    Vector3 trans(viewMatrix.matrix[0][3], viewMatrix.matrix[1][3], viewMatrix.matrix[2][3]);
    Vector3 invTrans(invViewMatrix * trans);

    invViewMatrix.matrix[0][3] = -invTrans.x;
    invViewMatrix.matrix[1][3] = -invTrans.y;
    invViewMatrix.matrix[2][3] = -invTrans.z;
    invViewMatrix.matrix[3][3] = 1;
}

void Camera::SetProjectionMatrix()
{
    GLfloat top = nearDist * (tan((3.14159/180.0f) * (viewAngle/2.0f)));
    GLfloat bot = -top;
    GLfloat right = top * aspect;
    GLfloat left = -right;

    projectionMatrix.matrix[0][0] = (2 * nearDist) / (right - left);
    projectionMatrix.matrix[0][2] = (right + left) / (right - left);
    projectionMatrix.matrix[1][1] = (2 * nearDist) / (top - bot);
    projectionMatrix.matrix[1][2] = (top + bot) / (top - bot);
    projectionMatrix.matrix[2][2] = (-(farDist + nearDist))/(farDist - nearDist);
    projectionMatrix.matrix[2][3] = (-2 * farDist * nearDist)/(farDist - nearDist);
    projectionMatrix.matrix[3][2] = -1;
    projectionMatrix.matrix[3][3] = 0;

    invProjectionMatrix.matrix[0][0] = 1/projectionMatrix.matrix[0][0];
    invProjectionMatrix.matrix[1][1] = 1/projectionMatrix.matrix[1][1];
    invProjectionMatrix.matrix[2][2] = 0;
    invProjectionMatrix.matrix[2][3] = 1/projectionMatrix.matrix[3][2];
    invProjectionMatrix.matrix[3][2] = 1/projectionMatrix.matrix[2][3];
    invProjectionMatrix.matrix[3][3] = -projectionMatrix.matrix[2][2] / (projectionMatrix.matrix[2][3] * projectionMatrix.matrix[3][2]);
}

void Camera::UpdateMatrices()
{
    bool notify = (updateViewMatrix || updateProjectionMatrix);

    if (updateViewMatrix)
    {
        SetViewMatrix();
        updateViewMatrix = false;
    }
    if (updateProjectionMatrix)
    {
        SetProjectionMatrix();
        updateProjectionMatrix = false;
    }

    // If the camera has changed, notify the observers
    if (notify)
        Notify();
}

Vector3 Camera::MouseToWorld(GLfloat xPos, GLfloat yPos)
{
    yPos = height - yPos - 1;
    Vector3 clip(xPos, yPos, 1);

    clip.x = clip.x / width;
    clip.y = clip.y / height;

    clip.x = clip.x * 2 - 1;
    clip.y = clip.y * 2 - 1;
    clip.z = clip.z * 2 - 1;

    Mat4x4 inverse = invViewMatrix * invProjectionMatrix;

    Vector3 result = inverse * clip;

    GLfloat w = inverse.matrix[3][0] * clip.x + 
                inverse.matrix[3][1] * clip.y + 
                inverse.matrix[3][2] * clip.z +
                inverse.matrix[3][3];

    result = result * (1/w);

    return result;
}

Vector3 Camera::GetPosition()
{
    return eye;
}
