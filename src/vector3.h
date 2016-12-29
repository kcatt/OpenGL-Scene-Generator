#ifndef __VECTOR_3__H_
#define __VECTOR_3__H_

#include <iostream>

class Vector3
{
    public:
        /********************
         * Public Variables *
         ********************/
        float x;
        float y;
        float z;

        /****************
         * Constructors *
         ****************/
        Vector3(const Vector3& v);
        Vector3(float x = 0, float y = 0, float z = 0);

        /********************
         * Public Functions *
         ********************/
        void  Scale(float scalar);
        float Dot(const Vector3& v) const;
        void  Cross(const Vector3& v);
        void  Reverse();
        float Magnitude() const;
        void  Normalize();
        void  Set(float x, float y, float z);
        void  Set(const Vector3& v);
        
        /********************
         * Static Functions *
         ********************/
        static Vector3 Cross(const Vector3& lhs, const Vector3& rhs);

        /********************
         * Friend Functions *
         ********************/
        friend Vector3 operator*(const Vector3& lhs, float scalar);
        friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
        friend std::ostream& operator<<(std::ostream& out, const Vector3& v);

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