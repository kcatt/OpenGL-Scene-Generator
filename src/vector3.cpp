#include <cmath>
#include "vector3.h"

// Friend Functions
Vector3 operator*(const Vector3& lhs, float scalar)
{
    Vector3 retVal(lhs);

    retVal.x *= scalar;
    retVal.y *= scalar;
    retVal.z *= scalar;

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

std::ostream& operator<<(std::ostream& out, const Vector3& v)
{
    out << v.x << " " << v.y << " " << v.z;
    return out;
}

Vector3::Vector3(const Vector3& v)
{
    this->Set(v);
}

Vector3::Vector3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::Scale(float scalar)
{
    x *= scalar;
    y *= scalar;
    z *= scalar;
}

float Vector3::Dot(const Vector3& v) const
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

float Vector3::Magnitude() const
{
    return (float)sqrt(this->Dot(*this));
}

void Vector3::Normalize()
{
    float magnitude = this->Magnitude();

    if (magnitude == 0)
    {
        std::cerr << "\nCannot normalize vector <0,0,0>!" << std::endl;
        return;
    }

    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}

void Vector3::Set(float x, float y, float z)
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

Vector3 Vector3::Cross(const Vector3& lhs, const Vector3& rhs)
{
    return Vector3(lhs.y*rhs.z - lhs.z*rhs.y,
            lhs.z*rhs.x - lhs.x*rhs.z,
            lhs.x*rhs.y - lhs.y*rhs.x);
}