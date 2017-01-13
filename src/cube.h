#ifndef __CUBE__H_
#define __CUBE__H_

#include "scene_object.h"

class Cube : public SceneObject
{
    public:
        /***************
         * Constructor *
         ***************/
        Cube();

        /***********************
         * Overloaded Function *
         ***********************/
        void Draw();
    
    private:
        static GLuint  indexArr[36];
        static bool    cubeSetUp;
        static GLuint  cubeVBO, cubeVAO, cubeEBO;

        void SetUpCube();
};

#endif