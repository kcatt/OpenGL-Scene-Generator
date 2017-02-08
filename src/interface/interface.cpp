#include "interface.h"

Interface::Interface()
{
    mainDialog = new MainDialog(screen, 10, 10);
}

Interface::Interface(nanogui::Screen* screen)
{
    this->screen = screen;
    mainDialog = new MainDialog(screen, 10, 10);
}

Interface::~Interface()
{
    if (mainDialog != NULL)
        delete mainDialog;
}

MainDialog* Interface::GetMainDialog()
{
    return mainDialog;
}