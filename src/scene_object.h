#ifndef __SCENE_OBJECT__H_
#define __SCENE_OBJECT__H_

// Included to get all of the required OpenGL headers
#include <GL/glew.h>
#include "transform.h"
#include "material.h"
#include "vector3.h"

class SceneObject
{
    public:
        SceneObject() {};

        /********************
         * Public Variables *
         ********************/
        Transform transform;
        Material  material;

        GLfloat* objectVerts = NULL;

        /**************
         * Destructor *
         **************/
        ~SceneObject();

        /********************
         * Public Functions *
         ********************/
        void SetModelMatrixLoc(GLuint location);

        /*********************
         * Virtual Functions *
         *********************/
        virtual void Draw();
        virtual void TellMaterials();
    
    protected:
        /***********************
         * Protected Variables *
         ***********************/
        GLuint modelMatrixLoc;

        /***********************
         * Protected Functions *
         ***********************/
        Vector3 CalculateFaceNormal(const Vector3& vert1, const Vector3& vert2, const Vector3& vert3);
};

#endif