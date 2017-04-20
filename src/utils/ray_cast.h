#ifndef __RAY_CAST__H_
#define __RAY_CAST__H_

#include <nanogui/nanogui.h>
#include <vector>
#include <memory>
#include "vector3.h"
#include "scene_object.h"
#include "aabb.h"
#include "camera.h"

class RayCast
{
    public:
        /****************
         * Constructors *
         ****************/
        RayCast(const Vector3& origin, const Vector3& direction);

        /********************
         * Public Functions *
         ********************/
        std::shared_ptr<SceneObject> IntersectTest(const std::vector<std::shared_ptr<SceneObject> >& objects);
        void SetCamera(Camera* cam);

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 origin;
        Vector3 direction;
        Vector3 invDirection;
        GLfloat magnitude;
        Camera* camera;

        /********************
         * Private Function *
         ********************/
        GLfloat Intersect(AABB& box);
};

#endif