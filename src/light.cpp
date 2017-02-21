#include "light.h"

Light::Light()
{
    SetColor(Color3(1, 1, 1));
    // Default position is 10 units above and in front of the origin
    SetPosition(Vector3(0, 10, 10));
}

Light::Light(const Vector3& position, const Color3& color)
{
    SetColor(color);
    SetPosition(position);
}

void Light::SetColor(const Color3& color)
{
    this->color = color;
}

Color3& Light::GetColor()
{
    return this->color;
}

void Light::SetPosition(const Vector3& position)
{   
    this->position = position;
}  

Vector3& Light::GetPosition()
{
    return this->position;
}