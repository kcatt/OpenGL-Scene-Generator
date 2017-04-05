#ifndef __DEF_OBJECT__H_
#define __DEF_OBJECT__H_

#include <vector>
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
        void AddObject(SceneObject* object);

        /*******************
         * Public Variable *
         *******************/
        std::string name;

    private:
        std::vector<SceneObject*> objects;
};

#endif