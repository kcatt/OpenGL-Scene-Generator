#include "dialog.h"

Dialog::Dialog(nanogui::Screen* screen, const std::string& windowLabel, int posX, int posY)
{
    SetScreen(screen);

    gui = new nanogui::FormHelper(screen);
    window = gui->addWindow(Eigen::Vector2i(posX, posY), windowLabel);
}

Dialog::~Dialog()
{
    if (gui != NULL)
        delete gui;
}

void Dialog::SetScreen(nanogui::Screen* screen)
{
    this->screen = screen;
}

// These are just wrapper functions provided to simplify the creation of dialogs
void Dialog::AddGroup(const std::string& caption)
{
    gui->addGroup(caption);
}

void Dialog::AddButton(const std::string& label, const std::function<void()>& callback)
{
    gui->addButton(label, callback);
}

void Dialog::AddVariable(const std::string& label, const std::function<void(const GLfloat&)>& setter, const std::function<GLfloat()>& getter)
{
    gui->addVariable(label, setter, getter, true);
}

void Dialog::AddVariable(const std::string& label, GLfloat& value)
{
    gui->addVariable(label, value, true);
}