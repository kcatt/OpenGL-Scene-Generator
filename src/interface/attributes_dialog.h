#ifndef __ATTRIBUTES_DIALOG__H_
#define __ATTRIBUTES_DIALOG__H_

#include <nanogui/nanogui.h>
#include "dialog.h"
#include "vector3.h"
#include "color3.h"

class AttributesDialog : public Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        AttributesDialog(nanogui::Screen* screen);

        /**************
         * Destructor *
         **************/
        ~AttributesDialog();

        /********************
         * Public Variables *
         ********************/
        Vector3* lightPosition;
        Color3*  lightColor;
        Color3*  ambientColor;
        Color3*  backgroundColor;

    private:
        /*********************
         * Private Variables *
         *********************/
        

        /*********************
         * Private Functions *
         *********************/
        void Create();
};

#endif