#ifndef __LIGHT__H_
#define __LIGHT__H_

#include "vector3.h"
#include "color3.h"

class Light
{
    public:
        /***************
         * Constructor *
         ***************/
        Light();
        Light(const Vector3& position, const Color3& color);

        /*******************
         * Public Function *
         *******************/
        void SetColor(const Color3& color);
        Color3& GetColor();
        void SetPosition(const Vector3& position);
        Vector3& GetPosition();

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 position;
        Color3  color;
};

#endif