#include <cmath>
#include "camera.h"
#include <iostream>

Camera::Camera()
{
    eye.Set(0, 0, 0);
    look.Set(0, 0, 0);
    u.Set(0, 0, 0);
    n.Set(0, 0, 0);
    v.Set(0, 0, 0);
    viewAngle = 0;
    aspect = 0;
    nearDist = 0;
    farDist = 0;
    updateViewMatrix = false;
    updateProjectionMatrix = false;
}

Camera::Camera(GLuint viewMatLoc, GLuint projectMatLoc)
{
    SetProjectionMatrixLoc(projectMatLoc);
    SetViewMatrixLoc(viewMatLoc);

    updateViewMatrix = false;
    updateProjectionMatrix = false;

    SetShape(45.0f, 800.0f, 600.0f, 0.1f, 200.0f);
    Set(Vector3(0, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
}

void Camera::Set(Vector3 eye, Vector3 look, Vector3 up)
{
    this->eye.Set(eye);
    this->look.Set(look);

    n.Set(eye.x - look.x, eye.y - look.y, eye.z - look.z);
    n.Normalize();
    u.Set(Vector3::Cross(up, n));
    u.Normalize();
    v.Set(Vector3::Cross(n, u));
    updateViewMatrix = true;
}

/* Rotate the camera about the Z-axis */
void Camera::Roll(GLfloat angle)
{
    GLfloat c = cos(3.14159/180 * angle);
    GLfloat s = sin(3.14159/180 * angle);

    Vector3 temp(u);

    u.Set(c*temp.x - s*v.x, c*temp.y - s*v.y, c*temp.z - s*v.z);
    v.Set(s*temp.x + c*v.x, s*temp.y + c*v.y, s*temp.z + c*v.z);

    updateViewMatrix = true;
}

/* Rotate the camera about the X-axis */
void Camera::Pitch(GLfloat angle)
{
    GLfloat c = cos(3.14159/180 * angle);
    GLfloat s = sin(3.14158/180 * angle);
    
    Vector3 temp(v);
    v.Set(c*temp.x - s*n.x, c*temp.y - s*n.y, c*temp.z - s*n.z);
    n.Set(s*temp.x + c*n.x, s*temp.y + c*n.y, s*temp.z + c*n.z);

    updateViewMatrix = true;
}

/* Rotate the camera about the Y-axis */
void Camera::Yaw(GLfloat angle)
{
    GLfloat c = cos (3.14159/180 * angle);
    GLfloat s = sin (3.14159/180 * angle);

    Vector3 temp (n);
    n.Set(c*temp.x - s*u.x, c*temp.y - s*u.y, c*temp.z - s*u.z);
    u.Set(s*temp.x + c*u.x, s*temp.y + c*u.y, s*temp.z + c*u.z);

    updateViewMatrix = true;
}

/* Function to translate the camera in a direction
 * Params: delU - Change in x direction,
           delV - Change in y direction,
           delN - Change in z direction */
void Camera::Slide(GLfloat delU, GLfloat delV, GLfloat delN)
{
    GLfloat delX = delU*u.x + delV*v.x + delN*n.x;
    GLfloat delY = delU*u.y + delV*v.y + delN*n.y;
    GLfloat delZ = delU*u.z + delV*v.z + delN*n.z;
    eye.Set(eye.x+delX, eye.y+delY, eye.z+delZ);
    
    updateViewMatrix = true;
}

void Camera::SetShape(GLfloat viewAngle, GLfloat width, GLfloat height, GLfloat nearDist, GLfloat farDist)
{
    this->viewAngle = viewAngle;
    this->width     = width;
    this->height    = height;
    this->aspect    = width/height;
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

void Camera::SetViewMatrixLoc(GLuint location)
{
    viewUniformLoc = location;
}

void Camera::SetProjectionMatrixLoc(GLuint location)
{
    projectionUniformLoc = location;
}

void Camera::SetViewMatrix()
{
    viewMatrix.matrix[0][0] = u.x;
    viewMatrix.matrix[0][1] = u.y;
    viewMatrix.matrix[0][2] = u.z;
    viewMatrix.matrix[0][3] = (-1 * eye).Dot(u);
    viewMatrix.matrix[1][0] = v.x;
    viewMatrix.matrix[1][1] = v.y;
    viewMatrix.matrix[1][2] = v.z;
    viewMatrix.matrix[1][3] = (-1 * eye).Dot(v);
    viewMatrix.matrix[2][0] = n.x;
    viewMatrix.matrix[2][1] = n.y;
    viewMatrix.matrix[2][2] = n.z;
    viewMatrix.matrix[2][3] = (-1 * eye).Dot(n);
    viewMatrix.matrix[3][0] = 0;
    viewMatrix.matrix[3][1] = 0;
    viewMatrix.matrix[3][2] = 0;
    viewMatrix.matrix[3][3] = 1;

    GLfloat viewMat[16];
    viewMatrix.ConvertToOpenGLMatrix(viewMat);

    glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, viewMat);
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

    GLfloat projectMatrix[16];

    projectionMatrix.ConvertToOpenGLMatrix(projectMatrix);

    glUniformMatrix4fv(projectionUniformLoc, 1, GL_FALSE, projectMatrix);
}

void Camera::UpdateMatrices()
{
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
}

Vector3 Camera::MouseToWorld(GLfloat xPos, GLfloat yPos)
{
    GLfloat x = 2.0 * xPos/width - 1;
    GLfloat y = 1 - 2.0 * yPos/height;
    Vector3 clip(x, y, -1);

    Vector3 eye = projectionMatrix.Inverse() * clip;
    eye.z = -1;

    eye.Normalize();
    Vector3 world = eye.MatMultiply(viewMatrix.Inverse(), false);
    world.Normalize(); 

    std::cout << world << std::endl;

    return world;
}

Vector3 Camera::GetPosition()
{
    return eye;
}