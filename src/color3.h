#ifndef __COLOR_3__H_
#define __COLOR_3__H_

class Color3
{
    public:
        /********************
         * Public Variables *
         ********************/
        float r;
        float g;
        float b;

        /****************
         * Constructors *
         ****************/
        Color3(float r = 0, float g = 0, float b = 0);
        Color3(const Color3& color);

        /********************
         * Public Functions *
         ********************/
        void Add(float r, float g, float b);
        void Add(const Color3& src, const Color3& refl);
        void Add(const Color3& color);
        void Set(float r, float g, float b);
        void Set(const Color3& color);
        void Build4Tuple(float v[]);

        /********************
         * Friend Functions *
         ********************/
        friend Color3 operator*(const float& scalar);
        friend Color3 operator*(const Color3& color);
        friend std::ostream& operator<<(std::ostream& out, const Color3& c);
        
        inline Color3 operator=(const Color3& v) {
            red = v.red;
            green = v.green;
            blue = v.blue;
            return *this;
        }
};

#endif
