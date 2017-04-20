#ifndef __DEF_OBJECT__H_
#define __DEF_OBJECT__H_

#include <vector>
#include <memory>
#include "scene_object.h"

class DefObject : public SceneObject
{
    public:
        /***************
         * Constructor *
         ***************/
        DefObject();
        DefObject(const std::string& name);

        /**************
         * Destructor *
         **************/
        ~DefObject() { }

        /***********************
         * Overloaded Function *
         ***********************/
        void Draw();

        /*******************
         * Public Function *
         *******************/
        void AddObject(std::shared_ptr<SceneObject> object);

        /*******************
         * Public Variable *
         *******************/
        std::string name;

    private:
        std::vector<std::shared_ptr<SceneObject> > objects;
};

#endif