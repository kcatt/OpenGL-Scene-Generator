#ifndef __AABB__H_
#define __AABB__H_

#include <vector>
#include "vector3.h"

class AABB
{
    public:
        /***************
         * Constructor *
         ***************/
        AABB(const AABB& aabb);
        AABB(const std::vector<Vector3>& vertices);

        /********************
         * Public Functions *
         ********************/
        void Generate(const std::vector<Vector3>& vertices);
        void Generate(const Vector3& minExtents, const Vector3& maxExtents);
        void Recalculate();
        /********************
         * Public Variables *
         ********************/
        Transform transform;

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 maxExtents;
        Vector3 minExtents;
        Vector3 center;
        Vector3 vertices[8];
};

#endif