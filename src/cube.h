#ifndef __CUBE__H_
#define __CUBE__H_

#include "scene_object.h"

class Cube : public SceneObject
{
    public:
        /***************
         * Constructor *
         ***************/
        Cube() {};

        /***********************
         * Overloaded Function *
         ***********************/
        void Draw();
}