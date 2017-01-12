#ifndef __COLOR_3__H_
#define __COLOR_3__H_

// Included to get all of the required OpenGL headers
#include <GL/glew.h>

class Color3
{
    public:
        /********************
         * Public Variables *
         ********************/
        GLfloat r;
        GLfloat g;
        GLfloat b;

        /****************
         * Constructors *
         ****************/
        Color3(GLfloat r = 0, GLfloat g = 0, GLfloat b = 0);
        Color3(const Color3& color);

        /********************
         * Public Functions *
         ********************/
        void Add(GLfloat r, GLfloat g, GLfloat b);
        void Add(const Color3& src, const Color3& refl);
        void Add(const Color3& color);
        void Set(GLfloat r, GLfloat g, GLfloat b);
        void Set(const Color3& color);
        void Build4Tuple(GLfloat v[]);
        Color3 operator*(GLfloat scalar) const;
        Color3 operator*(const Color3& color) const;

        /********************
         * Friend Functions *
         ********************/
        friend std::ostream& operator<<(std::ostream& out, const Color3& c);
        
        inline Color3 operator=(const Color3& v) {
            this->r = v.r;
            this->g = v.g;
            this->b = v.b;
            return *this;
        }
};

#endif
