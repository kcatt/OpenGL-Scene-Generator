#include "dialog.h"

Dialog::Dialog(nanogui::Screen* screen, const std::string& windowLabel, int posX, int posY)
{
    window = new nanogui::Window(screen, windowLabel);
    window->setPosition(Eigen::Vector2i(posX, posY));
    window->setLayout(new nanogui::GroupLayout());
    layoutWidget = window;
}

Dialog::Dialog(nanogui::Screen* screen, const std::string& windowLabel)
{
    window = new nanogui::Window(screen, windowLabel);
    window->setLayout(new nanogui::GroupLayout());
    window->center();
    layoutWidget = window;
}

Dialog::~Dialog()
{
    
}

// These are just wrapper functions provided to simplify the creation of dialogs
void Dialog::AddGroup(const std::string& caption)
{
    // The pointer doesn't need to be stored because it will be automatically freed at
    // the deletion of the parent window
    nanogui::Label* newLabel = new nanogui::Label(window, caption, "sans-bold");
    newLabel->setFixedHeight(10);
    layoutWidget = window;
}

void Dialog::AddButton(const std::string& label, const std::function<void()>& callback)
{
    nanogui::Button* button = new nanogui::Button(layoutWidget, label);
    button->setCallback(callback);
    button->setFixedHeight(25);
    button->setFontSize(18);
}

void Dialog::AddVariable(const std::string& label, const std::function<void(const GLfloat&)>& setter, const std::function<GLfloat()>& getter)
{
    nanogui::Label* newLabel = new nanogui::Label(layoutWidget, label);
    newLabel->setFixedHeight(15);
    nanogui::FloatBox<GLfloat>* variableBox = new nanogui::FloatBox<GLfloat>(layoutWidget);
    
    auto refresh = [variableBox, getter] {
        GLfloat value = getter();
        GLfloat current = variableBox->value();
        if (value != current)
            variableBox->setValue(value);
    };
    refresh();

    refreshCallbacks.push_back(refresh);

    variableBox->setCallback(setter);
    variableBox->setEditable(true);
    variableBox->setFixedHeight(20);
}

void Dialog::AddVariable(const std::string& label, GLfloat& value)
{
    AddVariable(label, [&](const GLfloat& val) { value = val; }, [&]() -> GLfloat { return value; });
}

void Dialog::SetLayout(nanogui::Orientation orientation, nanogui::Alignment align, int margin, int spacing)
{
    widget = new nanogui::Widget(window);
    widget->setLayout(new nanogui::BoxLayout(orientation, align, margin, spacing));
    layoutWidget = widget;
}

void Dialog::ClearLayout()
{
    layoutWidget = window;
}

void Dialog::Hide()
{
    window->setVisible(false);
}

void Dialog::Show()
{
    window->setVisible(true);
}

void Dialog::Refresh()
{
    for (auto const &callback : refreshCallbacks)
        callback();
}