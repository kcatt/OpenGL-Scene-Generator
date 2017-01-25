#ifndef __SCENE_OBJECT__H_
#define __SCENE_OBJECT__H_

// Included to get all of the required OpenGL headers
#include <GL/glew.h>
#include "transform.h"
#include "material.h"
#include "vector3.h"
#include "mesh.h"

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
        Mesh     mesh;

        /**************
         * Destructor *
         **************/
        ~SceneObject();

        /********************
         * Public Functions *
         ********************/
        void SetUniformLocations(GLuint model, GLuint ambient, GLuint diffuse, GLuint specular, GLuint emissive, GLuint specExponent);

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
        GLuint matAmbientLoc;
        GLuint matDiffuseLoc;
        GLuint matSpecularLoc;
        GLuint matEmissiveLoc;
        GLuint matSpecExponentLoc;
};

#endif