#include "object_dialog.h"
#include <iostream>

ObjectDialog::ObjectDialog(nanogui::Screen* screen, int posX, int posY) : Dialog(screen, "Object Properties", posX, posY)
{
    selectedObject = NULL;
    created = false;
}

void ObjectDialog::Create()
{
    if (created)
        return;
    
    AddGroup("Position");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("X:", [this](GLfloat x){ selectedObject->transform.position.x = x; selectedObject->transform.SetPosition(selectedObject->transform.position); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.position.x; });
    AddVariable("Y:", [this](GLfloat y){ selectedObject->transform.position.y = y; selectedObject->transform.SetPosition(selectedObject->transform.position); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.position.y; });
    AddVariable("Z:", [this](GLfloat z){ selectedObject->transform.position.z = z; selectedObject->transform.SetPosition(selectedObject->transform.position); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.position.z; });
    
    AddGroup("Rotation");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("X:", [this](GLfloat x){ selectedObject->transform.rotation.x = x; selectedObject->transform.SetRotation(selectedObject->transform.rotation); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.rotation.x; });
    AddVariable("Y:", [this](GLfloat y){ selectedObject->transform.rotation.y = y; selectedObject->transform.SetRotation(selectedObject->transform.rotation); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.rotation.y; });
    AddVariable("Z:", [this](GLfloat z){ selectedObject->transform.rotation.z = z; selectedObject->transform.SetRotation(selectedObject->transform.rotation); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.rotation.z; });

    AddGroup("Scale");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("X:", [this](GLfloat x){ selectedObject->transform.scale.x = x; selectedObject->transform.SetScale(selectedObject->transform.scale); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.scale.x; });
    AddVariable("Y:", [this](GLfloat y){ selectedObject->transform.scale.y = y; selectedObject->transform.SetScale(selectedObject->transform.scale); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.scale.y; });
    AddVariable("Z:", [this](GLfloat z){ selectedObject->transform.scale.z = z; selectedObject->transform.SetScale(selectedObject->transform.scale); selectedObject->boundBox->RecalculateFromTransform(); }, 
                      [this]{ return selectedObject->transform.scale.z; });
    
    AddGroup("Emissive:");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ selectedObject->material.emissive.r = r; }, [this]{ return selectedObject->material.emissive.r; });
    AddVariable("G:", [this](GLfloat g){ selectedObject->material.emissive.g = g; }, [this]{ return selectedObject->material.emissive.g; });
    AddVariable("B:", [this](GLfloat b){ selectedObject->material.emissive.b = b; }, [this]{ return selectedObject->material.emissive.b; });

    AddGroup("Diffuse:");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ selectedObject->material.diffuse.r = r; }, [this]{ return selectedObject->material.diffuse.r; });
    AddVariable("G:", [this](GLfloat g){ selectedObject->material.diffuse.g = g; }, [this]{ return selectedObject->material.diffuse.g; });
    AddVariable("B:", [this](GLfloat b){ selectedObject->material.diffuse.b = b; }, [this]{ return selectedObject->material.diffuse.b; });

    AddGroup("Ambient:");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ selectedObject->material.ambient.r = r; }, [this]{ return selectedObject->material.ambient.r; });
    AddVariable("G:", [this](GLfloat g){ selectedObject->material.ambient.g = g; }, [this]{ return selectedObject->material.ambient.g; });
    AddVariable("B:", [this](GLfloat b){ selectedObject->material.ambient.b = b; }, [this]{ return selectedObject->material.ambient.b; });

    AddGroup("Specular:");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ selectedObject->material.specular.r = r; }, [this]{ return selectedObject->material.specular.r; });
    AddVariable("G:", [this](GLfloat g){ selectedObject->material.specular.g = g; }, [this]{ return selectedObject->material.specular.g; });
    AddVariable("B:", [this](GLfloat b){ selectedObject->material.specular.b = b; }, [this]{ return selectedObject->material.specular.b; });

    ClearLayout();

    AddVariable("Specular Exponent:", [this](GLfloat val){ selectedObject->material.specularExponent = val; }, [this]{ return selectedObject->material.specularExponent; });

    created = true;
}