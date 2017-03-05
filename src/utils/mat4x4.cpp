#include "mat4x4.h"
#include <iostream>

Mat4x4 operator*(const Mat4x4& lhs, const Mat4x4& rhs)
{
    Mat4x4 retVal(lhs);

    retVal.PostMultiply(rhs);

    return retVal;
}

Mat4x4 operator*(const Mat4x4& lhs, GLfloat rhs)
{
    Mat4x4 copy(lhs);

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            copy.matrix[i][j] *= rhs;
        }
    }

    return copy;
}

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

Mat4x4 Mat4x4::Inverse()
{
    Mat4x4 inverse;

    GLfloat subFactor00 = matrix[2][2] * matrix[3][3] - matrix[3][2] * matrix[2][3];
    GLfloat subFactor01 = matrix[2][1] * matrix[3][3] - matrix[3][1] * matrix[2][3];
    GLfloat subFactor02 = matrix[2][1] * matrix[3][2] - matrix[3][1] * matrix[2][2];
    GLfloat subFactor03 = matrix[2][0] * matrix[3][3] - matrix[3][0] * matrix[2][3];
    GLfloat subFactor04 = matrix[2][0] * matrix[3][2] - matrix[3][0] * matrix[2][2];
    GLfloat subFactor05 = matrix[2][0] * matrix[3][1] - matrix[3][0] * matrix[2][1];
    GLfloat subFactor06 = matrix[1][2] * matrix[3][3] - matrix[3][2] * matrix[1][3];
    GLfloat subFactor07 = matrix[1][1] * matrix[3][3] - matrix[3][1] * matrix[1][3];
    GLfloat subFactor08 = matrix[1][1] * matrix[3][2] - matrix[3][1] * matrix[1][2];
    GLfloat subFactor09 = matrix[1][0] * matrix[3][3] - matrix[3][0] * matrix[1][3];
    GLfloat subFactor10 = matrix[1][0] * matrix[3][2] - matrix[3][0] * matrix[1][2];
    GLfloat subFactor11 = matrix[1][1] * matrix[3][3] - matrix[3][1] * matrix[1][3];
    GLfloat subFactor12 = matrix[1][0] * matrix[3][1] - matrix[3][0] * matrix[1][1];
    GLfloat subFactor13 = matrix[1][2] * matrix[2][3] - matrix[2][2] * matrix[1][3];
    GLfloat subFactor14 = matrix[1][1] * matrix[2][3] - matrix[2][1] * matrix[1][3];
    GLfloat subFactor15 = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
    GLfloat subFactor16 = matrix[1][0] * matrix[2][3] - matrix[2][0] * matrix[1][3];
    GLfloat subFactor17 = matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2];
    GLfloat subFactor18 = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

    inverse.matrix[0][0] = + (matrix[1][1] * subFactor00 - matrix[1][2] * subFactor01 + matrix[1][3] * subFactor02);
    inverse.matrix[0][1] = - (matrix[1][0] * subFactor00 - matrix[1][2] * subFactor03 + matrix[1][3] * subFactor04);
    inverse.matrix[0][2] = + (matrix[1][0] * subFactor01 - matrix[1][1] * subFactor03 + matrix[1][3] * subFactor05);
    inverse.matrix[0][3] = - (matrix[1][0] * subFactor02 - matrix[1][1] * subFactor04 + matrix[1][2] * subFactor05);

    inverse.matrix[1][0] = - (matrix[0][1] * subFactor00 - matrix[0][2] * subFactor01 + matrix[0][3] * subFactor02);
    inverse.matrix[1][1] = + (matrix[0][0] * subFactor00 - matrix[0][2] * subFactor03 + matrix[0][3] * subFactor04);
    inverse.matrix[1][2] = - (matrix[0][0] * subFactor01 - matrix[0][1] * subFactor03 + matrix[0][3] * subFactor05);
    inverse.matrix[1][3] = + (matrix[0][0] * subFactor02 - matrix[0][1] * subFactor04 + matrix[0][2] * subFactor05);

    inverse.matrix[2][0] = + (matrix[0][1] * subFactor06 - matrix[0][2] * subFactor07 + matrix[0][3] * subFactor08);
    inverse.matrix[2][1] = - (matrix[0][0] * subFactor06 - matrix[0][2] * subFactor09 + matrix[0][3] * subFactor10);
    inverse.matrix[2][2] = + (matrix[0][0] * subFactor11 - matrix[0][1] * subFactor09 + matrix[0][3] * subFactor12);
    inverse.matrix[2][3] = - (matrix[0][0] * subFactor08 - matrix[0][1] * subFactor10 + matrix[0][2] * subFactor12);

    inverse.matrix[3][0] = - (matrix[0][1] * subFactor13 - matrix[0][2] * subFactor14 + matrix[0][3] * subFactor15);
    inverse.matrix[3][1] = + (matrix[0][0] * subFactor13 - matrix[0][2] * subFactor16 + matrix[0][3] * subFactor17);
    inverse.matrix[3][2] = - (matrix[0][0] * subFactor14 - matrix[0][1] * subFactor16 + matrix[0][3] * subFactor18);
    inverse.matrix[3][3] = + (matrix[0][0] * subFactor15 - matrix[0][1] * subFactor17 + matrix[0][2] * subFactor18);

    GLfloat determinant =
        + matrix[0][0] * inverse.matrix[0][0]
        + matrix[0][1] * inverse.matrix[0][1]
        + matrix[0][2] * inverse.matrix[0][2]
        + matrix[0][3] * inverse.matrix[0][3];

    determinant = 1.0 / determinant;

    inverse = inverse * determinant;

    return inverse;

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