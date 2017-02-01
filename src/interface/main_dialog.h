#ifndef __MAIN_DIALOG__H_
#define __MAIN_DIALOG__H_

#include "dialog.h"
#include "scene.h"

class MainDialog : public Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        MainDialog();

        /**************
         * Destructor *
         **************/
        ~MainDialog();

        /********************
         * Public Functions *
         ********************/
        void SetScene(Scene* scene);

    private:
        /*********************
         * Private Variables *
         *********************/
        Scene* scene;

        /*********************
         * Private Functions *
         *********************/
        void Create();
};

#endif