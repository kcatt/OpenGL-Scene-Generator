#ifndef __CAMERA__H_
#define __CAMERA__H_

// Included to get all of the required OpenGL headers
#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include "vector3.h"
#include "mat4x4.h"

class Camera
{
    public:
        /****************
         * Constructors *
         ****************/
        Camera();
        Camera(GLuint viewMatLoc, GLuint projectMatLoc);

        /********************
         * Public Functions *
         ********************/
        void Set(Vector3 eye, Vector3 look, Vector3 up);
        void Roll(GLfloat angle);
        void Pitch(GLfloat angle);
        void Yaw(GLfloat angle);
        void Slide(GLfloat delU, GLfloat delV, GLfloat delN);
        void SetShape(GLfloat viewAngle, GLfloat width, GLfloat height, GLfloat nearDist, GLfloat farDist);
        void GetShape(GLfloat& viewAngle, GLfloat& aspect, GLfloat& nearDist, GLfloat& farDist);
        void SetViewMatrixLoc(GLuint location);
        void SetProjectionMatrixLoc(GLuint location);
        void UpdateMatrices();
        Vector3 MouseToWorld(GLfloat xPos, GLfloat yPos);
        Vector3 GetPosition();

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 eye, look;
        Vector3 u, v, n;
        GLfloat viewAngle, aspect, width, height, nearDist, farDist;
        GLuint  viewUniformLoc, projectionUniformLoc;
        bool    updateViewMatrix, updateProjectionMatrix;

        Mat4x4  projectionMatrix, viewMatrix;

        /********************
         * Private Function *
         ********************/
        void SetViewMatrix();
        void SetProjectionMatrix();
};

#endif