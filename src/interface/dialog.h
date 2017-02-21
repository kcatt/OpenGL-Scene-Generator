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
        Dialog(nanogui::Screen* helper, const std::string& windowLabel, int posX, int posY);
        Dialog(nanogui::Screen* helper, const std::string& windowLabel);

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
        void SetLayout(nanogui::Orientation orientation, nanogui::Alignment align, int margin = 0, int spacing = 0);
        void ClearLayout();
        void Hide();
        void Show();
        void Refresh();

    protected:
        /**********************
         * Protected Variable *
         **********************/
        bool useLayout;
        nanogui::Screen* screen;
        nanogui::Widget* widget;
        nanogui::Widget* layoutWidget;
        nanogui::ref<nanogui::Window> window;
        std::vector<std::function<void()>> refreshCallbacks;
};

#endif