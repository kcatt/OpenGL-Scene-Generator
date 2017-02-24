#ifndef __SCENE_OBJECT__H_
#define __SCENE_OBJECT__H_

// Included to get all of the required OpenGL headers
#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include "transform.h"
#include "material.h"
#include "vector3.h"
#include "mesh.h"
#include "aabb.h"

class SceneObject
{
    public:
        SceneObject() {}

        /********************
         * Public Variables *
         ********************/
        Transform transform;
        Material  material;
        AABB*     boundBox = NULL;
        Mesh      mesh;

        std::string type;

        /**************
         * Destructor *
         **************/
        virtual ~SceneObject() {}

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