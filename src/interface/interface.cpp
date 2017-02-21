#include "interface.h"

Interface::Interface(nanogui::Screen* screen)
{
    this->screen = screen;
    formHelper = new nanogui::FormHelper(screen);
    mainDialog = new MainDialog(screen, 10, 10);
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