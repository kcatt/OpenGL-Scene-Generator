#ifndef __SCENE_OBJECT__H_
#define __SCENE_OBJECT__H_

#include "transform.h"
#include "material.h"
#include "vector3.h"

class SceneObject
{
    public:
        /********************
         * Public Variables *
         ********************/
        Transform transform;
        Material  material;

        /*********************
         * Virtual Functions *
         *********************/
        virtual void Draw();
        virtual void TellMaterials();
};

#endif