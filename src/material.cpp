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
    textureType = 0;
    numParams = 0;
    reflectivity = transparency = 0.0;
    speedOfLight = specularExponent = .5;
    specularFraction = 0.0;
    surfaceRoughness = 1.0;
    ambient.Set(0.1 ,0.1, 0.1);
    diffuse.Set(0.8, 0.8, 0.8);
    specular.Set(0, 0, 0);
    emissive.Set(0, 0, 0);
}

void Material::Set(const Material& mat)
{
    textureType = mat.textureType;
    numParams = mat.numParams;
    for(int i = 0; i < numParams; i++)
        params[i] = mat.params[i];
    transparency = mat.transparency;
    speedOfLight = mat.speedOfLight;
    reflectivity = mat.reflectivity;
    specularExponent = mat.specularExponent;
    specularFraction = mat.specularFraction;
    surfaceRoughness = mat.surfaceRoughness;
    ambient.Set(mat.ambient);
    diffuse.Set(mat.diffuse);
    specular.Set(mat.specular);
    emissive.Set(mat.emissive);  
}