#ifndef __MAIN_DIALOG__H_
#define __MAIN_DIALOG__H_

#include "dialog.h"

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
        void SetSceneContext(void* context);
        void SetLoadCallback(void (*callback)(void* context, const std::string& fileName));

    private:
        /*********************
         * Private Variables *
         *********************/
        void (*loadCallback)(void* context, const std::string& fileName);
        void* sceneContext;

        /*********************
         * Private Functions *
         *********************/
        void Create();
        void OpenLoadDialog();
};

#endif