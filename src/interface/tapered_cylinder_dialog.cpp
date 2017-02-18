#include "tapered_cylinder_dialog.h"
#include <iostream>

TaperedCylinderDialog::TaperedCylinderDialog(nanogui::FormHelper* formHelper, const std::function<void()>& callback) : Dialog(formHelper, "Tapered Cylinder Insert")
{
    cylinderRadius = 1;
    Create(callback);
}

void TaperedCylinderDialog::Create(const std::function<void()>& callback)
{
    AddVariable("Top Radius:", [this](GLfloat x){ cylinderRadius = x; }, [this]{ return cylinderRadius; });
    AddButton("Insert", callback);
}