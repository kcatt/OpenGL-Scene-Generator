#ifndef __MAIN_DIALOG__H_
#define __MAIN_DIALOG__H_

#include "dialog.h"
#include "scene_object.h"

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
        void SetInsertCallback (void (*callback)(void* context, SceneObject* newObject));

    private:
        /*********************
         * Private Variables *
         *********************/
        void (*loadCallback)(void* context, const std::string& fileName);
        void (*saveCallback)(void* context, const std::string& fileName);
        void (*insertCallback)(void* context, SceneObject* newObject);
        void* sceneContext;

        /*********************
         * Private Functions *
         *********************/
        void Create();
        void OpenLoadDialog();
        void OpenSaveDialog();
        void Insert(const std::string& objType);
};

#endif