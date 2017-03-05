#include <cmath>
#include "vector3.h"

// Friend Functions
Vector3 operator*(const Vector3& lhs, GLfloat scalar)
{
    Vector3 retVal(lhs);

    retVal.x *= scalar;
    retVal.y *= scalar;
    retVal.z *= scalar;

    return retVal;
}

Vector3 operator*(GLfloat scalar, const Vector3& rhs)
{
    Vector3 retVal(rhs);

    retVal.x *= scalar;
    retVal.y *= scalar;
    retVal.z *= scalar;

    return retVal;
}

Vector3 operator*(const Mat4x4& matrix, const Vector3& rhs)
{
    GLfloat vectorArr[4] = { rhs.x, rhs.y, rhs.z, 1.0f };
    Vector3 retVal;

    retVal.x = matrix.matrix[0][0] * vectorArr[0] + 
               matrix.matrix[0][1] * vectorArr[1] + 
               matrix.matrix[0][2] * vectorArr[2] +
               matrix.matrix[0][3];
    retVal.y = matrix.matrix[1][0] * vectorArr[0] + 
               matrix.matrix[1][1] * vectorArr[1] + 
               matrix.matrix[1][2] * vectorArr[2] +
               matrix.matrix[1][3];
    retVal.z = matrix.matrix[2][0] * vectorArr[0] + 
               matrix.matrix[2][1] * vectorArr[1] + 
               matrix.matrix[2][2] * vectorArr[2] +
               matrix.matrix[2][3];

    return retVal;     
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 retVal(lhs);

    retVal.x += rhs.x;
    retVal.y += rhs.y;
    retVal.z += rhs.z;

    return retVal;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
    Vector3 retVal(lhs);

    retVal.x -= rhs.x;
    retVal.y -= rhs.y;
    retVal.z -= rhs.z;

    return retVal;
}

bool operator==(const Vector3& lhs, const Vector3& rhs)
{
    return ((lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.z == rhs.z));
}

std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    out << v.x << " " << v.y << " " << v.z;
    return out;
}

Vector3::Vector3(const Vector3& v)
{
    this->Set(v);
}

Vector3::Vector3(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::Scale(GLfloat scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

GLfloat Vector3::Dot(const Vector3& v) const
{
    return (this->x*v.x + this->y*v.y + this->z*v.z);
}

void Vector3::Cross(const Vector3& v)
{   
    Vector3 temp(this->y*v.z - this->z*v.y,
            this->z*v.x - this->x*v.z,
            this->x*v.y - this->y*v.x);
    *this = temp;
}

void Vector3::Reverse()
{
    this->x *= -1;
    this->y *= -1;
    this->z *= -1;
}

GLfloat Vector3::Magnitude() const
{
    return (GLfloat)sqrt(this->Dot(*this));
}

void Vector3::Normalize()
{
    GLfloat magnitude = this->Magnitude();

    if (magnitude == 0)
    {
        std::cerr << "Cannot normalize vector <0,0,0>!" << std::endl;
        return;
    }

    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

void Vector3::Set(GLfloat x, GLfloat y, GLfloat z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::Set(const Vector3& v)
{
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}

Vector3 Vector3::MatMultiply(const Mat4x4& mat, bool homogenous)
{
    if (homogenous)
    {
        return mat * *this;
    }
    else
    {   
        GLfloat vectorArr[4] = { x, y, z, 0.0f };
        Vector3 retVal;

        retVal.x = mat.matrix[0][0] * vectorArr[0] + 
                   mat.matrix[0][1] * vectorArr[1] + 
                   mat.matrix[0][2] * vectorArr[2];
        retVal.y = mat.matrix[1][0] * vectorArr[0] + 
                   mat.matrix[1][1] * vectorArr[1] + 
                   mat.matrix[1][2] * vectorArr[2];
        retVal.z = mat.matrix[2][0] * vectorArr[0] + 
                   mat.matrix[2][1] * vectorArr[1] + 
                   mat.matrix[2][2] * vectorArr[2];

        return retVal; 
    }
}

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.y*rhs.z - lhs.z*rhs.y,
            lhs.z*rhs.x - lhs.x*rhs.z,
            lhs.x*rhs.y - lhs.y*rhs.x);
}

Vector3 Vector3::Normalize(const Vector3& vecToNormalize)
{
    Vector3 retVal(vecToNormalize);
    retVal.Normalize();

    return retVal;
}