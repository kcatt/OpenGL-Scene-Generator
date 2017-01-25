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
        Color3   ambient;
        Color3   diffuse;
        Color3   specular;
        Color3   emissive;
        GLfloat  specularExponent;

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