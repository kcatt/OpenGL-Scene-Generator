#ifndef __INTERFACE__H_
#define __INTERFACE__H_

#include <vector>
#include "dialog.h"
#include "main_dialog.h"
#include "attributes_dialog.h"
#include "object_dialog.h"
#include <nanogui/nanogui.h>

class Interface 
{
    public:
        /***************
         * Constructor *
         ***************/
        Interface(nanogui::Screen* screen);

        /**************
         * Destructor *
         **************/
        ~Interface();

        /*******************
         * Public Function *
         *******************/
        MainDialog* GetMainDialog();
        ObjectDialog* GetObjectDialog();
        void Disable();
        void Enable();

        /********************
         * Public Variables *
         ********************/
        nanogui::Screen* screen;

    private:
        /*********************
         * Private Variables *
         *********************/
        MainDialog*   mainDialog;
        ObjectDialog* objectDialog;
        std::vector<Dialog> dialogs;
        nanogui::FormHelper* formHelper;
        bool enabled = true;
};

#endif