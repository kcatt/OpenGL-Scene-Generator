#include "object_dialog.h"
#include <iostream>

ObjectDialog::ObjectDialog(nanogui::Screen* screen) : Dialog(screen, "Global Attributes")
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
    AddVariable("X:", [this](GLfloat x){ selectedObject->transform.position.x = x; selectedObject->transform.SetPosition(selectedObject->transform.position); }, 
                      [this]{ return selectedObject->transform.position.x; });
    AddVariable("Y:", [this](GLfloat y){ selectedObject->transform.position.y = y; selectedObject->transform.SetPosition(selectedObject->transform.position); }, 
                      [this]{ return selectedObject->transform.position.y; });
    AddVariable("Z:", [this](GLfloat z){ selectedObject->transform.position.z = z; selectedObject->transform.SetPosition(selectedObject->transform.position); }, 
                      [this]{ return selectedObject->transform.position.z; });

    created = true;
                      /*
    AddGroup("Light Position");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("X:", [this](GLfloat x){ lightPosition->x = x; }, [this]{ return lightPosition->x; });
    AddVariable("Y:", [this](GLfloat y){ lightPosition->y = y; }, [this]{ return lightPosition->y; });
    AddVariable("Z:", [this](GLfloat z){ lightPosition->z = z; }, [this]{ return lightPosition->z; });

    AddGroup("Light Color");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ lightColor->r = r; }, [this]{ return lightColor->r; });
    AddVariable("G:", [this](GLfloat g){ lightColor->g = g; }, [this]{ return lightColor->g; });
    AddVariable("B:", [this](GLfloat b){ lightColor->b = b; }, [this]{ return lightColor->b; });

    AddGroup("Ambient Color");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ ambientColor->r = r; }, [this]{ return ambientColor->r; });
    AddVariable("G:", [this](GLfloat g){ ambientColor->g = g; }, [this]{ return ambientColor->g; });
    AddVariable("B:", [this](GLfloat b){ ambientColor->b = b; }, [this]{ return ambientColor->b; });

    AddGroup("Background Color");
    SetLayout(nanogui::Orientation::Horizontal, nanogui::Alignment::Middle, 0, 6);
    AddVariable("R:", [this](GLfloat r){ backgroundColor->r = r; }, [this]{ return backgroundColor->r; });
    AddVariable("G:", [this](GLfloat g){ backgroundColor->g = g; }, [this]{ return backgroundColor->g; });
    AddVariable("B:", [this](GLfloat b){ backgroundColor->b = b; }, [this]{ return backgroundColor->b; });

    ClearLayout();
    AddButton("Close", [this]{ Hide(); });*/
}