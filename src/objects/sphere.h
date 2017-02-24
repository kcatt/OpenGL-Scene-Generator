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
        Sphere();

        /**************
         * Destructor *
         **************/
        ~Sphere() 
        { 
            if (boundBox != NULL)
                delete boundBox;
        }

        /***********************
         * Overloaded Function *
         ***********************/
        void Draw();
    
    private:
        std::vector<Vector3> vertVector;

        void SetUpSphere();
        void SubdivideTriangles(Vector3 vert1, Vector3 vert2, Vector3 vert3, int level);
        void NormalizePoint(Vector3& p, GLfloat length);
};

#endif