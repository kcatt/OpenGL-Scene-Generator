#include "interface.h"

Interface::Interface(nanogui::Screen* screen)
{
    this->screen = screen;
    formHelper = new nanogui::FormHelper(screen);
    mainDialog = new MainDialog(formHelper, 10, 10);
}

Interface::~Interface()
{
    if (mainDialog != NULL)
        delete mainDialog;

    if (formHelper != NULL)
        delete formHelper;
}

MainDialog* Interface::GetMainDialog()
{
    return mainDialog;
}