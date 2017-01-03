#ifndef __MAT_4X4__H_
#define __MAT_4X4__H_

#include <iostream>

class Mat4x4
{
    public:
        /*******************
         * Public Variable *
         *******************/
        GLfloat matrix[4][4];
        
        /****************
         * Constructors *
         ****************/
        Mat4x4();
        Mat4x4(const Mat4x4& mat);

        /********************
         * Public Functions *
         ********************/
        void    SetIdentity();
        void    PostMultiply(const Mat4x4& mat);
        void    PreMultiply(const Mat4x4& mat);
        void    Set(const Mat4x4& mat);
        void    Set(const GLfloat mat[4][4]);
        Mat4x4  Transpose();

        // operator= cannot be defined using friend
        inline Mat4x4& operator=(const Mat4x4& rhs)
        {   
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    matrix[i][j] = rhs.matrix[i][j];
                }
            }

            return *this;
        }
};

#endif