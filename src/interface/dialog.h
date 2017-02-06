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
        Dialog(nanogui::Screen* screen, const std::string& windowLabel, int posX, int posY);

        /**************
         * Destructor *
         **************/
        ~Dialog();

        /********************
         * Public Functions *
         ********************/
        void SetScreen(nanogui::Screen* screen);

        // These are just wrapper functions provided to simplify the creation of dialogs
        void AddGroup(const std::string& caption);
        void AddButton(const std::string& label, const std::function<void()>& callback);
        void AddVariable(const std::string& label, const std::function<void(const GLfloat&)>& setter, const std::function<GLfloat()>& getter);
        void AddVariable(const std::string& label, GLfloat& value);

    protected:
        /**********************
         * Protected Variable *
         **********************/
        nanogui::Screen* screen;

    private:
        /*********************
         * Private Variables *
         *********************/
        nanogui::FormHelper *gui;
        nanogui::Window* window;
};

#endif