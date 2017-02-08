#ifndef __CUBE__H_
#define __CUBE__H_

#include "scene_object.h"
#include "mesh.h"

class Cube : public SceneObject
{
    public:
        /***************
         * Constructor *
         ***************/
        Cube();

        /**************
         * Destructor *
         **************/
        ~Cube() { }


        /***********************
         * Overloaded Function *
         ***********************/
        void Draw();
};

#endif