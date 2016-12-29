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

        /****************
         * Constructors *
         ****************/
        Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);
        Transform(const Transform& transform);

        /********************
         * Public Functions *
         ********************/
        void Translate(const Vector3& translation);
        void Translate(float x, float y, float z);
        void Rotate(const Vector3& rotation);
        void Rotate(float x, float y, float z);
        void Scale(const Vector3& scale);
        void Scale(float x, float y, flaot z);
        
        void SetPosition(const Vector3& position);
        void SetPosition(float x, float y, float z);
        void SetRotation(const Vector3& rotation);
        void SetRotation(float x, float y, float z);
        void SetScale(const Vector3& scale);
        void SetScale(float x, float y, float z);

        void Rotate(float angle, const Vector3& axis);

        std::ostream& operator<<(std::ostream& out, const Transform& t);

    private:
        /*********************
         * Private Variables *
         *********************/
        Mat4x4 affine;
        Mat4x4 invAffine;

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
