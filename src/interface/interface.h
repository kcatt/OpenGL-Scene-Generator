#ifndef __INTERFACE__H_
#define __INTERFACE__H_

#include <vector>
#include "dialog.h"
#include "main_dialog.h"
#include <nanogui/nanogui.h>

class Interface 
{
    public:
        /***************
         * Constructor *
         ***************/
        Interface();

        /*******************
         * Public Function *
         *******************/
        MainDialog* GetMainDialog();

    private:
        /*********************
         * Private Variables *
         *********************/
        MainDialog mainDialog;
        std::vector<Dialog> dialogs;
};

#endif