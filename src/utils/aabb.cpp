#include "aabb.h"
#include <limits>
#include <iostream>

#define POS_INF std::numeric_limits<GLfloat>::infinity()
#define NEG_INF -std::numeric_limits<GLfloat>::infinity()

AABB::AABB(const AABB& aabb)
{
    transform = aabb.transform;
    maxExtents = aabb.maxExtents;
    minExtents = aabb.minExtents;
    center = aabb.center;

    for (int i = 0; i < 8; i++)
    {
        vertices[i] = aabb.vertices[i];
        originalVertices[i] = aabb.originalVertices[i];
    }
}

AABB::AABB(const std::vector<Vector3>& vertices)
{
    Generate(vertices);

    for (int i = 0; i < 8; i++)
    {
        originalVertices[i] = this->vertices[i];
    }

    std::vector<Vector3> vertVec =
    {
        originalVertices[0], originalVertices[1], originalVertices[2],
        originalVertices[2], originalVertices[3], originalVertices[0],

        originalVertices[4], originalVertices[5], originalVertices[6],
        originalVertices[6], originalVertices[7], originalVertices[4],

        originalVertices[0], originalVertices[3], originalVertices[7],
        originalVertices[7], originalVertices[4], originalVertices[0],

        originalVertices[1], originalVertices[2], originalVertices[6],
        originalVertices[6], originalVertices[5], originalVertices[1],

        originalVertices[2], originalVertices[6], originalVertices[7],
        originalVertices[7], originalVertices[3], originalVertices[2],

        originalVertices[0], originalVertices[1], originalVertices[5],
        originalVertices[5], originalVertices[4], originalVertices[0]
    };
    
    mesh.Create(vertVec);
    mesh.SetUpGL();
    mesh.SetRenderMode(Mesh::MODE_WIRE);
}

void AABB::Generate(const std::vector<Vector3>& vertices)
{
    // Reset the max and min to negative and positive infinity respectively
    // so they get set properly from the new vertices
    minExtents.Set(POS_INF, POS_INF, POS_INF);
    maxExtents.Set(NEG_INF, NEG_INF, NEG_INF);

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
    vertices[0].Set(minExtents.x, minExtents.y, maxExtents.z); // bottom left F 
    vertices[1].Set(maxExtents.x, minExtents.y, maxExtents.z); // bottom right F
    vertices[2].Set(maxExtents.x, maxExtents.y, maxExtents.z); // top right F
    vertices[3].Set(minExtents.x, maxExtents.y, maxExtents.z); // top left F
    vertices[4].Set(minExtents.x, minExtents.y, minExtents.z); // bottom left B
    vertices[5].Set(maxExtents.x, minExtents.y, minExtents.z); // bottom right B 
    vertices[6].Set(maxExtents.x, maxExtents.y, minExtents.z); // top right B
    vertices[7].Set(minExtents.x, maxExtents.y, minExtents.z); // top left B

    center.Set((maxExtents.x + minExtents.x)/2.0f, (maxExtents.y + minExtents.y)/2.0f, (maxExtents.z + minExtents.z)/2.0f);
}

void AABB::RecalculateFromTransform()
{
    for (int i = 0; i < 8; i++)
    {
        vertices[i] = transform->affine * originalVertices[i];
    }

    std::vector<Vector3> boxVec(vertices, vertices + sizeof(vertices) / sizeof(Vector3));

    Generate(boxVec);
}
