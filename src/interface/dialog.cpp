#include "dialog.h"

Dialog::Dialog()
{

}

Dialog::~Dialog()
{
    
}

void Dialog::AddButton(const std::string& name, TwButtonCallback callback, void* data, const std::string def)
{

}

void Dialog::AddVariable(const std::string& name, TwType type, TwSetVarCallback setCallback, TwGetVarCallback getCallback, void* data, const std::string& def)
{

}

void Dialog::AddROVariable(const std::string& name, TwType type, const void* var, const std::string& def)
{

}

void Dialog::AddRWVariable(const std::string& name, TwType type, void* var, const std::String& def)
{

}

void Dialog::Display()
{

}
