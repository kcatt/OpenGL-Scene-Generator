#include "aabb.h"

AABB::AABB(const AABB& aabb)
{
    transform = aabb.transform;
    maxExtents = aabb.maxExtents;
    minExtents = aabb.minExtents;
    center = aabb.center;

    for (int i = 0; i < 8; i++)
    {
        vertices[i] = aabb.vertices[i];
    }
}

AABB::AABB(const std::vector<Vector3>& vertices)
{
    Generate(vertices);
}

void AABB::Generate(const std::vector<Vector3>& vertices)
{
    for (size_t i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].x > maxExtents.x)
            maxExtents.x = vertices[i].x;
        
        if (vertices[i].y > maxExtents.y)
            maxExtents.y = vertices[i].y;

        if (vertices[i].z > maxExtents.z)
            maxExtents.z = vertices[i].z;
        
        if (vertices[i].x < minExtents.x)
            minExtents.x = vertices[i].x;
        
        if (vertices[i].y < minExtents.y)
            minExtents.y = vertices[i].y;

        if (vertices[i].z < minExtents.z)
            minExtents.z = vertices[i].z;
    }

    Generate(minExtents, maxExtents);
}

void AABB::Generate(const Vector3& minExtents, const Vector3& maxExtents)
{
    vertices[0].Set(minExtents.x, minExtents.y, maxExtents.z);
    vertices[1].Set(maxExtents.x, minExtents.y, maxExtents.z);
    vertices[2].Set(maxExtents.x, maxExtents.y, maxExtents.z);
    vertices[3].Set(minExtents.x, maxExtents.y, maxExtents.z);
    vertices[4].Set(minExtents.x, minExtents.y, minExtents.z);
    vertices[5].Set(maxExtents.x, minExtents.y, minExtents.z);
    vertices[6].Set(maxExtents.x, maxExtents.y, minExtents.z);
    vertices[7].Set(minExtents.x, maxExtents.y, minExtents.z);

    center.Set((maxExtents.x + minExtents.x)/2.0f, (maxExtents.y + minExtents.y)/2.0f, (maxExtents.z + minExtents.z)/2.0f);
}

void AABB::RecalculateFromTransform()
{
    for (int i = 0; i < 8; i++)
    {
        vertices[i] = transform->affine * vertices[i];
    }

    std::vector<Vector3> boxVec(vertices, vertices + 8);

    Generate(boxVec);
}