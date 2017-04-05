#include "ray_cast.h"
#include <algorithm>
#include <iostream>

RayCast::RayCast(const Vector3& origin, const Vector3& direction)
{
    this->origin = origin;
    this->direction = direction;
    this->invDirection.Set(1/direction.x, 1/direction.y, 1/direction.z);
}

SceneObject* RayCast::IntersectTest(const std::vector<SceneObject*>& objects)
{   
    std::vector<GLfloat> intersectTimes;
    std::vector<SceneObject*> intersectObjects;

    for (size_t i = 0; i < objects.size(); i++)
    {
        GLfloat t = Intersect(*(objects[i]->boundBox));

        if (t > 0)
        {
            intersectTimes.push_back(t);
            intersectObjects.push_back(objects[i]);
        }
    }

    if (intersectTimes.empty())
        return NULL;

    size_t smallest = 0;

    for (size_t i = 1; i < intersectTimes.size(); i++)
    {
        if (intersectTimes[i] < intersectTimes[smallest])
            smallest = i;
    }

    return intersectObjects[smallest];
}

void RayCast::SetCamera(Camera* cam)
{
    camera = cam;
}

GLfloat RayCast::Intersect(AABB& box)
{
    box.RecalculateFromTransform();

    double t1 = (box.minExtents.x - origin.x)*invDirection.x;
    double t2 = (box.maxExtents.x - origin.x)*invDirection.x;
 
    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);
 
    t1 = (box.minExtents.y - origin.y)*invDirection.y;
    t2 = (box.maxExtents.y - origin.y)*invDirection.y;
 
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    t1 = (box.minExtents.z - origin.z)*invDirection.z;
    t2 = (box.maxExtents.z - origin.z)*invDirection.z;
 
    tmin = std::max(tmin, std::min(t1, t2));
    tmax = std::min(tmax, std::max(t1, t2));

    if (tmax > std::max(tmin, 0.0))
        return tmax;
    else
        return -1;

}
