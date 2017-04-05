#include "main_dialog.h"

#include <iostream>
#include <nfd/nfd.h>

#include "cube.h"
#include "sphere.h"
#include "tapered_cylinder.h"
#include "mesh_3vn.h"

MainDialog::MainDialog(nanogui::Screen* screen, int posX, int posY) : Dialog(screen, "Main", posX, posY)
{
    Create();

    taperedCylinderDialog = new TaperedCylinderDialog(screen, [this]{ Insert("TaperedCylinder"); });
    taperedCylinderDialog->Hide();

    attributesDialog = new AttributesDialog(screen);
    attributesDialog->Hide();
}

MainDialog::~MainDialog()
{

}

void MainDialog::Create()
{
    AddButton("Load SDL File", [this]{ OpenLoadDialog(); });
    AddButton("Save SDL File", [this]{ OpenSaveDialog(); });
    AddButton("Global Attributes", [this]{ attributesDialog->Show(); });
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

void MainDialog::SetAttributesPointers(Vector3* lightPosition, Color3* lightColor, Color3* ambientColor, Color3* backgroundColor)
{
    attributesDialog->lightPosition   = lightPosition;
    attributesDialog->lightColor      = lightColor;
    attributesDialog->ambientColor    = ambientColor;
    attributesDialog->backgroundColor = backgroundColor;

    attributesDialog->Create();
    attributesDialog->Refresh();
}

void MainDialog::OpenLoadDialog()
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog( NULL, NULL, &outPath );

    if (result == NFD_OKAY)
    {
        loadCallback(sceneContext, std::string(outPath));
        delete outPath;
    }
}

void MainDialog::OpenSaveDialog()
{
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_SaveDialog( NULL, NULL, &outPath );

    if (result == NFD_OKAY)
    {
        saveCallback(sceneContext, std::string(outPath));
        delete outPath;
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
    }

    insertCallback(sceneContext, newObject);
}
