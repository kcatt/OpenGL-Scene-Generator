#include "interface.h"

Interface::Interface(nanogui::Screen* screen)
{
    this->screen = screen;
    mainDialog = new MainDialog(screen, 10, 10);
    objectDialog = new ObjectDialog(screen, 540, 10);
    objectDialog->Hide();
}

Interface::~Interface()
{
    if (mainDialog != NULL)
        delete mainDialog;

    if (objectDialog != NULL)
        delete objectDialog;

    if (formHelper != NULL)
        delete formHelper;
}

MainDialog* Interface::GetMainDialog()
{
    return mainDialog;
}

ObjectDialog* Interface::GetObjectDialog()
{
    return objectDialog;
}

void Interface::Disable()
{
    mainDialog->Hide();

    for (size_t i = 0; i < dialogs.size(); i++)
    {
        dialogs[i].Hide();
    }

    enabled = false;
}

void Interface::Enable()
{
    mainDialog->Show();

    enabled = true;
}
