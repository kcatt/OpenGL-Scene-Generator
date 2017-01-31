#ifndef __DIALOG__H_
#define __DIALOG__H_ 

#include <AntTweakBar.h>

class Dialog
{
    public:
        /***************
         * Constructor *
         ***************/
        Dialog();

        /**************
         * Destructor *
         **************/
        ~Dialog();

        /********************
         * Public Functions *
         ********************/
        // These are just wrapper functions provided to simplify the creation of dialogs
        void AddButton(const std::string& name, TwButtonCallback callback, void* data, const std::string def);
        void AddVariable(const std::string& name, TwType type, TwSetVarCallback setCallback, TwGetVarCallback getCallback, void* data, const std::string& def);
        void AddROVariable(const std::string& name, TwType type, const void* var, const std::string& def);
        void AddRWVariable(const std::string& name, TwType type, void* var, const std::String& def);
        void Display();

    protected:
        /**********************
         * Protected Variable *
         **********************/
        TwBar* bar;
};

#endif