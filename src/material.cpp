#include "material.h"

Material::Material()
{
    SetDefault();
}

Material::Material(const Material& mat)
{
    Set(mat);
}

void Material::SetDefault()
{
    specularExponent = 0;
    ambient.Set(0.1 ,0.1, 0.1);
    diffuse.Set(0.8, 0.8, 0.8);
    specular.Set(0, 0, 0);
    emissive.Set(0, 0, 0);
}

void Material::Set(const Material& mat)
{
    specularExponent = mat.specularExponent;
    ambient.Set(mat.ambient);
    diffuse.Set(mat.diffuse);
    specular.Set(mat.specular);
    emissive.Set(mat.emissive);
}