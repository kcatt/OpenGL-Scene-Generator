#ifndef __MAIN_DIALOG__H_
#define __MAIN_DIALOG__H_

#include <nanogui/nanogui.h>
#include <memory>
#include "dialog.h"
#include "scene_object.h"
#include "tapered_cylinder_dialog.h"
#include "attributes_dialog.h"
#include "vector3.h"
#include "color3.h"

class MainDialog : public Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        MainDialog(nanogui::Screen* screen, int posX, int posY);

        /**************
         * Destructor *
         **************/
        ~MainDialog();

        /********************
         * Public Functions *
         ********************/
        void SetSceneContext   (void* context);
        void SetLoadCallback   (void (*callback)(void* context, const std::string& fileName));
        void SetSaveCallback   (void (*callback)(void* context, const std::string& fileName));
        void SetInsertCallback (void (*callback)(void* context, std::shared_ptr<SceneObject> newObject));
        void SetAttributesPointers(Vector3* lightPosition, Color3* lightColor, Color3* ambientColor, Color3* backgroundColor);

    private:
        /*********************
         * Private Variables *
         *********************/
        void (*loadCallback)(void* context, const std::string& fileName);
        void (*saveCallback)(void* context, const std::string& fileName);
        void (*insertCallback)(void* context, std::shared_ptr<SceneObject> newObject);
        void* sceneContext;
        TaperedCylinderDialog* taperedCylinderDialog;
        AttributesDialog* attributesDialog;

        /*********************
         * Private Functions *
         *********************/
        void Create();
        void OpenLoadDialog();
        void OpenSaveDialog();
        void Insert(const std::string& objType);
};

#endif