#ifndef __TAPERED_CYLINDER_DIALOG__H_
#define __TAPERED_CYLINDER_DIALOG__H_

#include <functional>
#include <nanogui/nanogui.h>
#include "dialog.h"

class TaperedCylinderDialog : public Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        TaperedCylinderDialog(nanogui::FormHelper* formHelper, const std::function<void()>& callback);

        /********************
         * Public Variables *
         ********************/
        GLfloat cylinderRadius;

    private:
        /*********************
         * Private Functions *
         *********************/
        void Create(const std::function<void()>& callback);
};

#endif