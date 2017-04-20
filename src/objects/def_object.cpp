#include "def_object.h"

DefObject::DefObject()
{
    type = "use ";
    name = "";
}

DefObject::DefObject(const std::string& name)
{
    this->name = name;
    type = "use " + name;
}

void DefObject::AddObject(std::shared_ptr<SceneObject> object)
{
    objects.push_back(object);
}

void DefObject::Draw()
{
    for (auto object : objects)
    {
        object->modelViewMatrix = object->modelViewMatrix * transform.affine;
        object->Draw();
        object->modelViewMatrix = object->modelViewMatrix * transform.invAffine;
    }
}