#include <iostream>
#include "color3.h"

std::ostream& operator<<(std::ostream& out, const Color3& c)
{
    out << c.r << " " << c.g << " " << c.b;
    return out;
}

Color3 Color3::operator*(GLfloat scalar) const
{
    Color3 temp(*this);
    temp.r *= scalar;
    temp.g *= scalar;
    temp.b *= scalar;
    return temp;
}

Color3 Color3::operator*(const Color3& color) const
{
    Color3 temp(*this);
    temp.r *= color.r;
    temp.g *= color.g;
    temp.b *= color.b;
    return temp;
}

Color3::Color3(GLfloat r, GLfloat g, GLfloat b)
{
    this->Set(r, g, b);
}

Color3::Color3(const Color3& color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}

void Color3::Add(GLfloat r, GLfloat g, GLfloat b)
{
    this->r += r;
    this->g += g;
    this->b += b;
}

// Adds the product of the source color and reflection coefficient to the color
void Color3::Add(const Color3& src, const Color3& refl)
{
    this->r += (src.r * refl.r);
    this->g += (src.g * refl.g);
    this->b += (src.b * refl.b);
}

void Color3::Add(const Color3& color)
{
    this->r += color.r;
    this->g += color.g;
    this->b += color.b;
}

void Color3::Set(GLfloat r, GLfloat g, GLfloat b)
{
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color3::Set(const Color3& color)
{
    this->r = color.r;
    this->g = color.g;
    this->b = color.b;
}

// Makes 4-tuple from this color. Index 3 indicates homogenous.
void Color3::Build4Tuple(GLfloat v[])
{
    v[0] = this->r;
    v[1] = this->g;
    v[2] = this->b;
    v[3] = 1.0f;
}