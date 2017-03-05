#ifndef __MAT_4X4__H_
#define __MAT_4X4__H_

#include <iostream>
#ifndef __gl_h_
    #include <glad/glad.h>
#endif

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
        Mat4x4  Inverse();
        void    ConvertToOpenGLMatrix(GLfloat matrix[16]); 

        void Print()
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    std::cout << matrix[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }

        /*******************
         * Friend Function *
         *******************/
        friend Mat4x4 operator*(const Mat4x4& rhs, const Mat4x4& lhs);
        friend Mat4x4 operator*(const Mat4x4& rhs, GLfloat lhs);

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