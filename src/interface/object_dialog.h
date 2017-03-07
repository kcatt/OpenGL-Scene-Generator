#ifndef __OBJECT_DIALOG__H_
#define __OBJECT_DIALOG__H_

#include "dialog.h"
#include "scene_object.h"

class ObjectDialog : public Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        ObjectDialog(nanogui::Screen* screen);

        /**************
         * Destructor *
         **************/
        //~ObjectDialog();

        /*******************
         * Public Function *
         *******************/
        void Create();

        /********************
         * Public Variables *
         ********************/
        SceneObject* selectedObject;

    private:
        /*********************
         * Private Variables *
         *********************/
        bool created;
};

#endif