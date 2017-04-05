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

void DefObject::AddObject(SceneObject* object)
{
    objects.push_back(object);
}

void DefObject::Draw()
{
    for (SceneObject* object : objects)
    {
        object->transform.affine = transform.affine * object->transform.affine;
        object->Draw();
        object->transform.affine = transform.invAffine * object->transform.affine;
    }
}