#ifndef __TRANSFORM__H_
#define __TRANSFORM__H_

/*                                                             
*                                                              * 
* NEED TO DO CALCULATIONS TO TURN AXIS ROTATIONS INTO EULER    *
* ANGLES. Wikipedia: Rotation formalisms in three dimensions.  *
*                                                              *
*/

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
        void Scale(const Vector3& scale);
        void Scale(GLfloat x, GLfloat y, GLfloat z);
        
        void SetPosition(const Vector3& position);
        void SetPosition(GLfloat x, GLfloat y, GLfloat z);
        void SetRotation(const Vector3& rotation);
        void SetRotation(GLfloat x, GLfloat y, GLfloat z);
        void SetScale(const Vector3& scale);
        void SetScale(GLfloat x, GLfloat y, GLfloat z);

        void Rotate(GLfloat angle, const Vector3& axis);

        friend std::ostream& operator<<(std::ostream& out, const Transform& t);

    private:
        /*********************
         * Private Variables *
         *********************/
        // define rotation matrices to use to find rotations
        Mat4x4 rotationMat;
        Mat4x4 invRotation;

        /*********************
         * Private Functions *
         *********************/
        void ApplyTransform();
        void CheckRotation();
        void ResetRotationMatrices();
};

#endif
