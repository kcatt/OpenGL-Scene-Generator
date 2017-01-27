#ifndef __TAPERED_CYLINDER__H_
#define __TAPERED_CYLINDER__H_

#include <GL/glew.h>
#include <vector>
#include "scene_object.h"
#include "vector3.h"

class TaperedCylinder : public SceneObject
{
    public:
        /***************
        * Constructor *
        ***************/
        TaperedCylinder();

        /**************
        * Destructor *
        **************/
        ~TaperedCylinder() { }


        /**********************
        * Overloaded Function *
        ***********************/
        void Draw();

        /*******************
         * Public Function *
         *******************/
        void SetTopRadius(GLfloat radius);
        void Generate();

    private:
        /********************
         * Private Variable *
         ********************/
        bool    generated;
        GLfloat topRadius;
        std::vector<Vector3> vertVector;

        std::vector<Vector3> baseVector;
        std::vector<Vector3> baseRing;
        std::vector<Vector3> topVector;
        std::vector<Vector3> topRing;
        std::vector<Vector3> sideVector;

        /*********************
         * Private Functions *
         *********************/
        void GenerateBase();
        void GenerateTop();
        void GenerateSides();
        void GenerateCompleteMesh();
};

#endif