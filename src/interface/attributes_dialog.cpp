#include "attributes_dialog.h"
#include <iostream>

AttributesDialog::AttributesDialog(nanogui::FormHelper* formHelper, const std::function<void()>& callback) : Dialog(formHelper, "Tapered Cylinder Insert")
{
    cylinderRadius = 1;
    Create(callback);
}

void AttributesDialog::Create(const std::function<void()>& callback)
{
    nanogui::Widget* widget = NULL;
    AddGroup("Light Position");

    widget = new nanogui::Widget(window);
    widget->setLayout(new nanogui::BoxLayout(nanogui::Orientation::Horizontal, nanogui::ALignment::middle, 0, 6));
    AddVariable("X:", [this](GLfloat x){ lightPosition.x = x; }, [this]{ return lightPosition.x; });
    AddVariable("Y:", [this](GLfloat y){ lightPosition.y = y; }, [this]{ return lightPosition.y; });
    AddVariable("Z:", [this](GLfloat z){ lightPosition.z = z; }, [this]{ return lightPosition.z; });
    AddVariable("Top Radius:", [this](GLfloat x){ cylinderRadius = x; }, [this]{ return cylinderRadius; });
    AddButton("Insert", callback);
}