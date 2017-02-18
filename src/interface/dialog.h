#ifndef __DIALOG__H_
#define __DIALOG__H_ 

#include <nanogui/nanogui.h>
#include <functional>

class Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        Dialog(nanogui::FormHelper* helper, const std::string& windowLabel, int posX, int posY);
        Dialog(nanogui::FormHelper* helper, const std::string& windowLabel);

        /**************
         * Destructor *
         **************/
        ~Dialog();

        /********************
         * Public Functions *
         ********************/
        // These are just wrapper functions provided to simplify the creation of dialogs
        void AddGroup(const std::string& caption);
        void AddButton(const std::string& label, const std::function<void()>& callback);
        void AddVariable(const std::string& label, const std::function<void(const GLfloat&)>& setter, const std::function<GLfloat()>& getter);
        void AddVariable(const std::string& label, GLfloat& value);
        void Hide();
        void Show();

    protected:
        /**********************
         * Protected Variable *
         **********************/
        nanogui::FormHelper* formHelper;
        nanogui::ref<nanogui::Window> window;
        nanogui::FormHelper *gui;
};

#endif