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
        static std::vector<GLuint>  indexVector;
        static std::vector<Vector3> vertVector;
        static std::vector<Vector3> reducedVertVector;
        static std::vector<GLfloat> reducedVertArray;
        //static 
        static bool    sphereSetUp;
        static GLuint  sphereVBO, sphereVAO, sphereEBO;

        void SetUpSphere();
        void SubdivideTriangles(Vector3 vert1, Vector3 vert2, Vector3 vert3, int level);
        void ReduceVertexVector();
        void ConvertVectorsToGLArrays();
};

#endif