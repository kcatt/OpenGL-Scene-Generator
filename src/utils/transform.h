#ifndef __TRANSFORM__H_
#define __TRANSFORM__H_

#include "mat4x4.h"
#include "vector3.h"

class Transform
{
    public:
        /********************
         * Public Variables *
         ********************/
        Vector3 position;
        Vector3 rotation;
        Vector3 scale;

        Mat4x4  affine;
        Mat4x4  invAffine;

        /****************
         * Constructors *
         ****************/
        Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);
        Transform(const Transform& transform);
        Transform();

        /********************
         * Public Functions *
         ********************/
        void Translate(const Vector3& translation);
        void Translate(GLfloat x, GLfloat y, GLfloat z);
        void Rotate(const Vector3& rotation);
        void Rotate(GLfloat x, GLfloat y, GLfloat z);
        void IncreaseScale(const Vector3& scale);
        void IncreaseScale(GLfloat x, GLfloat y, GLfloat z);
        
        void SetPosition(const Vector3& position);
        void SetPosition(GLfloat x, GLfloat y, GLfloat z);
        void SetRotation(const Vector3& rotation);
        void SetRotation(GLfloat x, GLfloat y, GLfloat z);
        void SetRotation(GLfloat angle, const Vector3& axis);
        void RotateAxis(GLfloat angle, const Vector3& axis);
        void SetScale(const Vector3& scale);
        void SetScale(GLfloat x, GLfloat y, GLfloat z);

        void SetDefault();

        friend std::ostream& operator<<(std::ostream& out, const Transform& t);

        // operator= cannot be defined using friend
        inline Transform& operator=(const Transform& rhs)
        {
            position = rhs.position;
            rotation = rhs.rotation;
            scale = rhs.scale;
            affine = rhs.affine;
            invAffine = rhs.invAffine;
            rotationMat = rhs.rotationMat;
            invRotation = rhs.invRotation;

            return *this;
        }
Mat4x4 invRotation;
    private:
        /*********************
         * Private Variables *
         *********************/
        // define rotation matrices to use to find rotations
        Mat4x4 rotationMat;
        

        /*********************
         * Private Functions *
         *********************/
        void ApplyTransform();
        void CheckRotation();
        void ResetMatrices();
        void Rotate(GLfloat angle, const Vector3& axis);
};

#endif
