#ifndef __VECTOR_3__H_
#define __VECTOR_3__H_

#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include <iostream>
#include "mat4x4.h"

class Vector3
{
    public:
        /********************
         * Public Variables *
         ********************/
        GLfloat x;
        GLfloat y;
        GLfloat z;

        /****************
         * Constructors *
         ****************/
        Vector3(const Vector3& v);
        Vector3(GLfloat x = 0, GLfloat y = 0, GLfloat z = 0);

        /********************
         * Public Functions *
         ********************/
        void    Scale(GLfloat scalar);
        GLfloat Dot(const Vector3& v) const;
        void    Cross(const Vector3& v);
        void    Reverse();
        GLfloat Magnitude() const;
        void    Normalize();
        void    Set(GLfloat x, GLfloat y, GLfloat z);
        void    Set(const Vector3& v);
        
        /********************
         * Static Functions *
         ********************/
        static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);
        static Vector3 Normalize(const Vector3& vecToNormalize);

        /********************
         * Friend Functions *
         ********************/
        friend Vector3 operator*(const Vector3& lhs, GLfloat scalar);
        friend Vector3 operator*(GLfloat scalar, const Vector3& rhs);
        friend Vector3 operator*(const Mat4x4& matrix, const Vector3& rhs);
        friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
        friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
        friend std::ostream& operator<<(std::ostream& out, const Vector3& v);
        friend bool operator==(const Vector3& lhs, const Vector3& rhs);

        // operator= cannot be defined using friend
        inline Vector3& operator=(const Vector3& rhs)
        {
            x = rhs.x;
            y = rhs.y;
            z = rhs.z;

            return *this;
        }
};

#endif