#ifndef __MATERIAL__H_
#define __MATERIAL__H_

#include "vector3.h"
#include "color3.h"

class Material
{
    public:
        /********************
         * Public Variables *
         ********************/
        Color3 ambient, diffuse, specular, emissive;
        int numParams;
        GLdouble params[10];
        int textureType;
        float specularExponent, reflectivity, transparency, speedOfLight;
        float specularFraction, surfaceRoughness;

        /****************
         * Constructors *
         ****************/
        Material();
        Material(const Material& mat);

        /********************
         * Public Functions *
         ********************/
        void Set(const Material & m);
        void SetDefault();
};

#endif