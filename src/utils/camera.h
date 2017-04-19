#ifndef __CAMERA__H_
#define __CAMERA__H_

// Included to get all of the required OpenGL headers
#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include "vector3.h"
#include "mat4x4.h"
#include "iobservable.h"

class Camera : public IObservable<Camera>
{
    public:
        /****************
         * Constructors *
         ****************/
        Camera();

        /********************
         * Public Functions *
         ********************/
        void Set(Vector3 eye, Vector3 look, Vector3 up);
	void SetFromAxes(Vector3 backward, Vector3 right, Vector3 up, Vector3 eye);
        void Roll(GLfloat angle);
        void Pitch(GLfloat angle);
        void Yaw(GLfloat angle);
        void Slide(GLfloat delU, GLfloat delV, GLfloat delN);
        void SetShape(GLfloat viewAngle, GLint width, GLint height, GLfloat nearDist, GLfloat farDist);
        void GetShape(GLfloat& viewAngle, GLfloat& aspect, GLfloat& nearDist, GLfloat& farDist);
	void GetShape(GLfloat& viewAngle, GLfloat& width, GLfloat& height, GLfloat& nearDist, GLfloat& farDist);
        void UpdateMatrices();
        Vector3 MouseToWorld(GLfloat xPos, GLfloat yPos);
        Vector3 GetPosition();

        /********************
         * Public Variables *
         ********************/
        Mat4x4  projectionMatrix, viewMatrix;
        Vector3 backward, right, up;
        Vector3 eye, look;

    private:
        /*********************
         * Private Variables *
         *********************/
        GLfloat viewAngle, aspect, nearDist, farDist;
        GLint   width, height;
        bool    updateViewMatrix, updateProjectionMatrix;

        Mat4x4  invProjectionMatrix, invViewMatrix;

        /********************
         * Private Function *
         ********************/
        void SetViewMatrix();
        void SetProjectionMatrix();
};

#endif
