#ifndef __SCENE__H_
#define __SCENE__H_

#include <GL/glew.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "transform.h"
#include "material.h"
#include "color3.h"
#include "scene_object.h"

// Enums for the tokens of the sdl file
enum mTokenType {
    IDENT, LIGHT, ROTATE, TRANSLATE,
    SCALE, PUSH, POP, IDENTITYAFFINE,
    GLOBALAMBIENT, BACKGROUND, MINREFLECTIVITY,
    MINTRANSPARENCY, MAXRECURSIONDEPTH, MAKEPIXMAP, CUBE,
    SPHERE, TORUS, PLANE, SQUARE, TAPEREDCYLINDER, TEAPOT,
    MESH, DEFAULTMATERIALS, AMBIENT, DIFFUSE,SPECULAR,
    SPECULARFRACTION, SURFACEROUGHNESS,EMISSIVE, SPECULAREXPONENT,
    SPEEDOFLIGHT, TRANSPARENCY,REFLECTIVITY, PARAMETERS, TEXTURE,
    LFTCURLY, RGHTCURLY, DEF, USE, T_NULL, F_EOF, UNKNOWN
};

class Scene 
{
    public:
        /****************
         * Constructors *
         ****************/
        Scene();
        Scene(const std::string& fileName);

        /**************
         * Destructor *
         **************/
        ~Scene();

        /********************
         * Public Functions *
         ********************/
        void DrawScene(void);
        void SetBackground(const Color3& color);
        void FreeScene(void);
        void MakeLights(void);
        void ReadFile(const std::string& fileName);
        void SetModelMatrixLoc(GLuint location);

    private:
        /*********************
         * Private Variables *
         *********************/
        int currLine;
        int nextLine;
        Color3  backgroudColor; 
        Color3  ambientColor;
        int     maxRecursionDepth;
        GLfloat minReflectivity;
        GLfloat minTransparency;
        GLuint  modelMatrixLoc;
        Transform   currTransform;
        Material    currMaterial;
        vector<SceneObject*>                  objects;
        std::unique_ptr<std::ifstream>        inFile;
        std::unique_ptr<std::stringstream>    fileStream;
        
        /*********************
         * Private Functions *
         *********************/
        std::string NextToken(void);
        GLfloat     GetFloat(void);
        bool        IsIdentifier(const std::string& keyword);
        void        CleanUp(void);
        mTokenType  WhichToken(const std::string& keyword);
        void        GetObject(void);
};

#endif