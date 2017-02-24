#ifndef __RAY_CAST__H_
#define __RAY_CAST__H_

#include <nanogui/nanogui.h>
#include <vector>
#include "vector3.h"
#include "scene_object.h"

class RayCast
{
    public:
        /****************
         * Constructors *
         ****************/
        RayCast();
        RayCast(const Vector3& origin, const Vector3& direction);

        /********************
         * Public Functions *
         ********************/
        SceneObject* IntersectTest(std::vector<SceneObject*> objects);

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 origin;
        Vector3 direction;
        GLfloat magnitude;
};

#endif