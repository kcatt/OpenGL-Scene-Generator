#include "dialog.h"

Dialog::Dialog(nanogui::FormHelper* helper, const std::string& windowLabel, int posX, int posY)
{
    formHelper = helper;
    window = formHelper->addWindow(Eigen::Vector2i(posX, posY), windowLabel);
}

Dialog::Dialog(nanogui::FormHelper* helper, const std::string& windowLabel)
{
    formHelper = helper;
    window = formHelper->addWindow(Eigen::Vector2i(0, 0), windowLabel);
    window->center();
}

Dialog::~Dialog()
{
    
}

// These are just wrapper functions provided to simplify the creation of dialogs
void Dialog::AddGroup(const std::string& caption)
{
    formHelper->addGroup(caption);
}

void Dialog::AddButton(const std::string& label, const std::function<void()>& callback)
{
    formHelper->addButton(label, callback);
}

void Dialog::AddVariable(const std::string& label, const std::function<void(const GLfloat&)>& setter, const std::function<GLfloat()>& getter)
{
    formHelper->addVariable(label, setter, getter, true);
}

void Dialog::AddVariable(const std::string& label, GLfloat& value)
{
    formHelper->addVariable(label, value, true);
}

void Dialog::Hide()
{
    window->setVisible(false);
}

void Dialog::Show()
{
    window->setVisible(true);
}