#ifndef __SPHERE__H_
#define __SPHERE__H_

#include "scene_object.h"
#include <vector>

class Sphere : public SceneObject
{
    public:
        /***************
         * Constructor *
         ***************/
        Sphere() {};

        /***********************
         * Overloaded Function *
         ***********************/
        void Draw();
    
    private:
        static vector<GLfloat> indexVector;
        static vector<GLfloat> vertVector;
        static vector<GLfloat> reducedVertVector;
        //static 
        static bool    sphereSetUp;
        static GLuint  sphereVBO, sphereVAO, sphereEBO;

        void SetUpCube();
};

#endif