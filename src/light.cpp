#include "light.h"

Light::Light()
{
    SetColor(Color3(1, 1, 1));
    SetPosition(Vector3(0, 0, 0));
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

Color3 Light::GetColor()
{
    return this->color;
}

void Light::SetPosition(const Vector3& position)
{   
    this->position = position;
}  

Vector3 Light::GetPosition()
{
    return this->position;
}
