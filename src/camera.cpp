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

    SetShape(45.0f, 800.0f/600.0f, 0.1f, 200.0f);
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
    
    n.Set(n * c + v * s);
    v.Set(Vector3::Cross(u, n));  

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

void Camera::SetShape(GLfloat viewAngle, GLfloat aspect, GLfloat nearDist, GLfloat farDist)
{
    this->viewAngle = viewAngle;
    this->aspect    = aspect;
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
    Mat4x4 mat;

    mat.matrix[0][0] = u.x;
    mat.matrix[0][1] = u.y;
    mat.matrix[0][2] = u.z;
    mat.matrix[0][3] = (-1 * eye).Dot(u);
    mat.matrix[1][0] = v.x;
    mat.matrix[1][1] = v.y;
    mat.matrix[1][2] = v.z;
    mat.matrix[1][3] = (-1 * eye).Dot(v);
    mat.matrix[2][0] = n.x;
    mat.matrix[2][1] = n.y;
    mat.matrix[2][2] = n.z;
    mat.matrix[2][3] = (-1 * eye).Dot(n);
    mat.matrix[3][0] = 0;
    mat.matrix[3][1] = 0;
    mat.matrix[3][2] = 0;
    mat.matrix[3][3] = 1;

    GLfloat viewMatrix[16];
    mat.ConvertToOpenGLMatrix(viewMatrix);

    glUniformMatrix4fv(viewUniformLoc, 1, GL_FALSE, viewMatrix);
}

void Camera::SetProjectionMatrix()
{
    Mat4x4 mat;

    GLfloat top = nearDist * (tan((3.14159/180.0f) * (viewAngle/2.0f)));
    GLfloat bot = -top;
    GLfloat right = top * aspect;
    GLfloat left = -right;

    mat.matrix[0][0] = (2 * nearDist) / (right - left);
    mat.matrix[0][2] = (right + left) / (right - left);
    mat.matrix[1][1] = (2 * nearDist) / (top - bot);
    mat.matrix[1][2] = (top + bot) / (top - bot);
    mat.matrix[2][2] = (-(farDist + nearDist))/(farDist - nearDist);
    mat.matrix[2][3] = (-2 * farDist * nearDist)/(farDist - nearDist);
    mat.matrix[3][2] = -1;
    mat.matrix[3][3] = 0;

    GLfloat projectMatrix[16];

    mat.ConvertToOpenGLMatrix(projectMatrix);

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