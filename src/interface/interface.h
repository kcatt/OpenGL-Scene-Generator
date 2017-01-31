#ifndef __INTERFACE__H_
#define __INTERFACE__H_

#include <vector>
#include <AntTweakBar.h>
#include "dialog.h"
#include "main_dialog.h"

class Interface 
{
    public:
        /***************
         * Constructor *
         ***************/
        Interface();

    private:
        MainDialog mainDialog;
        std::vector<Dialog> dialogs;
};

#endif