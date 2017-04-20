#ifndef __SCENE__H_
#define __SCENE__H_

#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include "transform.h"
#include "material.h"
#include "color3.h"
#include "scene_object.h"
#include "light.h"
#include "interface.h"
#include "camera.h"

// Enums for the tokens of the sdl file
enum mTokenType {
    IDENT, LIGHT, ROTATE, TRANSLATE,
    SCALE, PUSH, POP, IDENTITYAFFINE,
    GLOBALAMBIENT, BACKGROUND, CUBE,
    SPHERE, TORUS, PLANE, SQUARE, TAPEREDCYLINDER, TEAPOT,
    MESH, DEFAULTMATERIALS, AMBIENT, DIFFUSE, SPECULAR,
    SURFACEROUGHNESS, EMISSIVE, SPECULAREXPONENT,
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
        bool ReadFile(const std::string& fileName);
        void SetModelUniformLocations(GLuint model, GLuint ambient, GLuint diffuse, GLuint specular, GLuint emissive, GLuint specExponent);
        void SetLightUniformLocations(GLuint position, GLuint color, GLuint ambient);
        void SetModelViewUniformLocation(GLuint modelView);
        void SetBoundsModelViewUnformLocation(GLuint modelView);
        void SetExportFileName(const std::string& fileName);
        void Export(const std::string& fileName);
        void Export();
        void Insert(std::shared_ptr<SceneObject> newObject);
        void SetUpMainDialog();
        void SetSelectedObject(std::shared_ptr<SceneObject> obj);
        void ResetRenderModes();
        void SetCamera(Camera* cam);
        void DrawSelectedBounds();
        void SaveCamera(const std::string& fileName);
        void LoadCamera(const std::string& fileName);

        /********************
         * Static Functions *
         ********************/
        static void ReadFunctionForwarder(void* context, const std::string& fileName);
        static void ExportFunctionForwarder(void* context, const std::string& fileName);
        static void InsertFunctionForwarder(void* context, std::shared_ptr<SceneObject> newObject);

        /*******************
         * Public Variable *
         *******************/
        Interface* interface = NULL;
        Color3     backgroundColor; 
        std::vector<std::shared_ptr<SceneObject>> objects;

    private:
        /*********************
         * Private Variables *
         *********************/
        int currLine;
        int nextLine;
        Light   light;
        Color3  ambientColor;
        Transform    currTransform;
        Material     currMaterial;
        Camera*      camera;
        
        std::string exportFileName;
        std::vector<std::string>            comments;
        std::shared_ptr<SceneObject>        selectedObject;
        std::unique_ptr<std::ifstream>      inFile;
        std::unique_ptr<std::stringstream>  fileStream;
        std::map<std::string, std::shared_ptr<DefObject> > defObjects;
        
        GLuint modelViewMatrixLoc;
        GLuint modelMatrixLoc;
        GLuint matAmbientLoc;
        GLuint matDiffuseLoc;
        GLuint matSpecularLoc;
        GLuint matEmissiveLoc;
        GLuint matSpecExponentLoc;
        GLuint lightPositionLoc;
        GLuint lightColorLoc;
        GLuint lightAmbientLoc;
        GLuint boundsModelViewMatrixLoc;

        /*********************
         * Private Functions *
         *********************/
        std::string NextToken(void);
        GLfloat     GetFloat(void);
        bool        IsIdentifier(const std::string& keyword);
        void        CleanUp(void);
        mTokenType  WhichToken(const std::string& keyword);
        bool        GetObject(void);
        void        SetUpLight(void);
};

#endif