#include "mat4x4.h"
#include <iostream>

Mat4x4::Mat4x4()
{
    SetIdentity();
}

Mat4x4::Mat4x4(const Mat4x4& mat)
{
    this->Set(mat);
}

void Mat4x4::SetIdentity()
{
    matrix[0][0] = 1; matrix[0][1] = 0; matrix[0][2] = 0; matrix[0][3] = 0;
    matrix[1][0] = 0; matrix[1][1] = 1; matrix[1][2] = 0; matrix[1][3] = 0;
    matrix[2][0] = 0; matrix[2][1] = 0; matrix[2][2] = 1; matrix[2][3] = 0;
    matrix[3][0] = 0; matrix[3][1] = 0; matrix[3][2] = 0; matrix[3][3] = 1;
}

void Mat4x4::PostMultiply(const Mat4x4& mat)
{
    Mat4x4 temp(*this);
    GLfloat sum;
   
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sum = 0;
            for (int k = 0; k < 4; k++)
                sum += temp.matrix[i][k] * mat.matrix[k][j];
            matrix[i][j] = sum;
        }
    }
}

void Mat4x4::PreMultiply(const Mat4x4& mat)
{
    Mat4x4 temp(*this);
    GLfloat sum;
   
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            sum = 0;
            for (int k = 0; k < 4; k++)
                sum +=  mat.matrix[i][k] * temp.matrix[k][j];
            matrix[i][j] = sum;
        }
    }
}

void Mat4x4::Set(const Mat4x4& mat)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->matrix[i][j] = mat.matrix[i][j];
        }
    }
}

void Mat4x4::Set(const GLfloat mat[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i][j] = mat[i][j];
        }
    }
}

Mat4x4 Mat4x4::Transpose()
{
    Mat4x4 retVal;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            retVal.matrix[i][j] = this->matrix[j][i];
        }
    }

    return retVal;
}

// Converts the internal matrix into the column-major 1D array that OpenGL expects
void Mat4x4::ConvertToOpenGLMatrix(GLfloat matrix[16])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i + j * 4] = this->matrix[i][j];
        }
    }
}
