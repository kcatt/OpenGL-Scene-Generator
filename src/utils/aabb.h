#ifndef __AABB__H_
#define __AABB__H_

#include <vector>
#include "vector3.h"
#include "transform.h"
#include "mesh.h"

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
        void RecalculateFromTransform();

        /********************
         * Public Variables *
         ********************/
        // Pointer to the object's transform
        Transform* transform;
        Vector3 maxExtents;
        Vector3 minExtents;
        Mesh    mesh;

    private:
        /*********************
         * Private Variables *
         *********************/
        Vector3 center;
        Vector3 vertices[8];
        Vector3 originalVertices[8];
};

#endif