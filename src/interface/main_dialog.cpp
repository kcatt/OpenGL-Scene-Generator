#include "main_dialog.h"

#include <iostream>
#include <nfd/nfd.h>

MainDialog::MainDialog(nanogui::Screen* screen, int posX, int posY) : Dialog(screen, "Main", posX, posY)
{
    Create();
}

MainDialog::~MainDialog()
{

}

void MainDialog::Create()
{
    AddGroup("Load/Save");
    AddButton("Load Scene", [this]{ OpenLoadDialog(); });
    AddButton("Save Scene", []{ std::cout << "Saving..." << std::endl; });
}

void MainDialog::SetSceneContext(void* context)
{
    sceneContext = context;
}

void MainDialog::SetLoadCallback(void (*callback)(void* context, const std::string& fileName))
{
    loadCallback = callback;
}

void MainDialog::OpenLoadDialog()
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog( NULL, NULL, &outPath );

    if (result == NFD_OKAY)
    {
        std::cout << outPath << std::endl;
        loadCallback(sceneContext, std::string(outPath));
        delete outPath;
    }
    else if (result == NFD_CANCEL)
    {
        std::cout << "Canceled!" << std::endl;
    }
}