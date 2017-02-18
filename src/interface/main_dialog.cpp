#include "main_dialog.h"

#include <iostream>
#include <nfd/nfd.h>

#include "cube.h"
#include "sphere.h"
#include "tapered_cylinder.h"
#include "mesh_3vn.h"

MainDialog::MainDialog(nanogui::FormHelper* formHelper, int posX, int posY) : Dialog(formHelper, "Main", posX, posY)
{
    Create();

    taperedCylinderDialog = new TaperedCylinderDialog(formHelper, [this]{ Insert("TaperedCylinder"); });
    taperedCylinderDialog->Hide();
}

MainDialog::~MainDialog()
{

}

void MainDialog::Create()
{
    AddButton("Load SDL File", [this]{ OpenLoadDialog(); });
    AddButton("Save SDL File", [this]{ OpenSaveDialog(); });
    AddButton("Global Attributes", []{ std::cout << "Global attributes..." << std::endl; });
    AddGroup("Insert");
    AddButton("Cube", [this]{ Insert("Cube"); });
    AddButton("Sphere", [this]{ Insert("Sphere"); });
    AddButton("Tapered Cylinder", [this]{ Insert("Cylinder"); });
    AddButton("Import 3VN Mesh", [this]{ Insert("Mesh"); });
}

void MainDialog::SetSceneContext(void* context)
{
    sceneContext = context;
}

void MainDialog::SetLoadCallback(void (*callback)(void* context, const std::string& fileName))
{
    loadCallback = callback;
}

void MainDialog::SetSaveCallback(void (*callback)(void* context, const std::string& fileName))
{
    saveCallback = callback;
}

void MainDialog::SetInsertCallback(void (*callback)(void* context, SceneObject* newObject))
{
    insertCallback = callback;
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

void MainDialog::OpenSaveDialog()
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_SaveDialog( NULL, NULL, &outPath );

    if (result == NFD_OKAY)
    {
        std::cout << outPath << std::endl;
        saveCallback(sceneContext, std::string(outPath));
        delete outPath;
    }
    else if (result == NFD_CANCEL)
    {
        std::cout << "Canceled!" << std::endl;
    }
}

void MainDialog::Insert(const std::string& objType)
{
    SceneObject* newObject;

    if (objType == "Cube")
    {
        newObject = new Cube;
    }
    else if (objType == "Sphere")
    {
        newObject = new Sphere;
    }
    else if (objType == "Cylinder")
    {
        taperedCylinderDialog->Show();
        return;
    }
    else if (objType == "TaperedCylinder")
    {
        newObject = new TaperedCylinder;
        ((TaperedCylinder*)newObject)->SetTopRadius(taperedCylinderDialog->cylinderRadius);
        ((TaperedCylinder*)newObject)->Generate();
        taperedCylinderDialog->Hide();
    }
    else if (objType == "Mesh")
    {
        nfdchar_t *outPath = NULL;
        nfdresult_t result = NFD_OpenDialog( NULL, NULL, &outPath );

        if (result == NFD_OKAY)
        {
            newObject = new Mesh3VN(std::string(outPath));
            delete outPath;
        }
        else if (result == NFD_CANCEL)
        {
            std::cout << "Canceled!" << std::endl;
            return;
        }
    }

    insertCallback(sceneContext, newObject);
}