#ifndef __CAMERA__H_
#define __CAMERA__H_

// Included to get all of the required OpenGL headers
#include <GL/glew.h>
#include "vector3.h"
#include "mat4x4.h"

class Camera
{
    public:
        /***************
         * Constructor *
         ***************/
        Camera();

        /********************
         * Public Functions *
         ********************/
        void Set(Vector3 eye, Vector3 look, Vector3 up);
        void Roll(GLfloat angle);
        void Pitch(GLfloat angle);
        void Yaw(GLfloat angle);
        void Slide(GLfloat delU, GLfloat delV, GLfloat delN);
        void SetShape(GLfloat viewAngle, GLfloat aspect, GLfloat nearDist, GLfloat farDist);
        void GetShape(GLfloat& viewAngle, GLfloat& aspect, GLfloat& nearDist, GLfloat& farDist);
        void SetViewMatrixLoc(GLuint location);
        void SetProjectionMatrixLoc(GLuint location);

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 eye, look;
        Vector3 u, v, n;
        GLfloat viewAngle, aspect, nearDist, farDist;
        GLuint  viewUniformLoc, projectionUniformLoc;

        /********************
         * Private Function *
         ********************/
        void SetViewMatrix();
        void SetProjectionMatrix();
};

#endif