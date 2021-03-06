#include "scene.h"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include "cube.h"
#include "sphere.h"
#include "tapered_cylinder.h"
#include "mesh_3vn.h"
#include "main_dialog.h"
#include "object_dialog.h"

Scene::Scene() {
    currMaterial.SetDefault();
    backgroundColor.Set(0.2f, 0.3f, 0.3f);
    ambientColor.Set(0.1f,0.1f,0.1f);

    SetUpMainDialog();
}

Scene::Scene(const std::string& fileName) {
    Scene();
    ReadFile(fileName);
}

Scene::~Scene() {
    FreeScene();
}

std::string Scene::NextToken(void)
{
    char nextChar;
    std::string token = "";
    int lastChar = 1;

    // Do nothing if the file stream doesn't exist or is at the end of file
    if (!fileStream || fileStream->eof())
        return token;
    
    while (fileStream->get(nextChar))
    {
        if (fileStream->eof())
            return token;
           
        switch(nextChar)
        {
            case '\n':
                nextLine++;
            // If some form of whitespace
            case ' ' :
            case '\t':
            case '\a':
            case '\b':
            case '\v':
            case '\f':
            case '\r': 
            {
                if (lastChar == 0) 
                {
                    return token;
                }
                break;
            }
            case '{': 
            {
                token = nextChar;
                return token;
            }
            case '}': 
            {
                token = nextChar;
                return token;
            }
            case '!': 
            {
                std::string comment = "";
                // This is a comment. Read the rest of the line and discard
                while (nextChar != '\n' && fileStream->get(nextChar))
                {   
                    comment += nextChar;
                }
                comments.push_back(comment);
                nextLine++;
                break;
            }
            default: 
            {
                token = token + nextChar;
                lastChar = 0;

                if ((fileStream->peek() == '{') ||
                    (fileStream->peek() == '}')) 
                {
                    if (lastChar == 0)  
                    {
                        return token;
                    } 
                    else 
                    {
                        fileStream->get(nextChar);
                        token = nextChar;
                        return token;
                    }
                }
                currLine = nextLine;
            }
        }
    }

    return " ";
}

// Clear the vectors in the scene
void Scene::FreeScene(void)
{
    SetSelectedObject(NULL);
    
    for (auto object : objects)
        object = nullptr;

    objects.clear();
    camera->ClearObservers();
}

GLfloat Scene::GetFloat(void)
{
    std::stringstream temp;
    GLfloat number;
    std::string nextToken = NextToken();
    temp << nextToken;

    if (!(temp >> number)) 
    {
        std::cerr << "Line " << currLine << ": Error getting float!" << std::endl;
        exit(-1);
    }
    else
    {
        char c;

        if ((temp >> c))
        {
            std::cerr << "Line " << currLine << ": Error getting float! Character(s) found in number!" << std::endl;
            exit(-1);
        }
    }

    return number;
}

bool Scene::IsIdentifier(const std::string& keyword)
{
    if (!isalpha(keyword[0]))
        return false;
    
    for (size_t count = 1; count < keyword.length(); count++)
    {
        if ((!isalnum(keyword[count])) && (keyword[count] != '.'))
            return false;
    }

    return true;
}

bool Scene::ReadFile(const std::string& fileName)
{
    LoadCamera(fileName);
    currMaterial.SetDefault();
    backgroundColor.Set(0.2f, 0.3f, 0.3f);
    ambientColor.Set(0.1f,0.1f,0.1f);
    
    FreeScene();

    inFile = std::make_unique<std::ifstream>(fileName.c_str());

    if (!(*inFile))
    {
        std::cout << "Cannot find or open file: " << fileName << std::endl;
        return false;
    }
    
    fileStream = std::make_unique<std::stringstream>();
    currLine = nextLine = 1;
    char nextChar;

    // Read the whole file
    while (inFile->get(nextChar)) 
    {
        *fileStream << nextChar;
    }

    // Read the file stream and get all of the objects
    while(GetObject());

    // Close the file object and delete the allocated memory
    inFile->close();

    return true;
}

mTokenType Scene::WhichToken(const std::string& keyword)
{
    if (keyword == "light" )
        return LIGHT;
    if (keyword == "rotate" )
        return ROTATE;
    if (keyword == "translate" )
        return TRANSLATE;
    if (keyword == "scale")
        return SCALE;
    if (keyword == "push")
        return PUSH;
    if (keyword == "pop")
        return POP;
    if (keyword == "identityAffine")
        return IDENTITYAFFINE;
    if (keyword == "cube")
        return CUBE;
    if (keyword == "sphere")
        return SPHERE;
    if (keyword == "torus")
        return TORUS;
    if (keyword == "plane")
        return PLANE;
    if (keyword == "taperedCylinder")
        return TAPEREDCYLINDER;
    if (keyword == "teapot")
        return TEAPOT;
    if (keyword == "mesh")
        return MESH;
    if (keyword == "defaultMaterials")
        return DEFAULTMATERIALS;
    if (keyword == "ambient")
        return AMBIENT;
    if (keyword == "diffuse")
        return DIFFUSE;
    if (keyword == "specular")
        return SPECULAR;
    if (keyword == "emissive")
        return EMISSIVE;
    if (keyword == "specularExponent")
        return SPECULAREXPONENT;
    if (keyword == "globalAmbient")
        return GLOBALAMBIENT;
    if (keyword == "background")
        return BACKGROUND;
    if (keyword == "{")
        return LFTCURLY;
    if (keyword == "}")
        return RGHTCURLY;
    if (keyword == "def")
        return DEF;
    if (keyword == "use")
        return USE;
    if (keyword == " ")
        return T_NULL;
    if (keyword == "square")
        return SQUARE;
    if (IsIdentifier(keyword))
        return IDENT;
    return UNKNOWN;
}

void Scene::DrawScene(void)
{
    SetUpLight();

    for (size_t i = 0; i < objects.size(); i++)
        objects[i]->Draw();
}

bool Scene::GetObject(void)
{
    std::string  nextStr;
    mTokenType   type;

    while ((type = (WhichToken(nextStr = NextToken()))) != T_NULL) {
        std::shared_ptr<SceneObject> newObject(nullptr);

        switch(type) {
            case LIGHT: 
            {
                Vector3 position;
                Color3  color;
                position.x = GetFloat();
                position.y = GetFloat();
                position.z = GetFloat();
                color.r = GetFloat();
                color.g = GetFloat();
                color.b = GetFloat();
                light.SetPosition(position);
                light.SetColor(color);
                break;
            }
            case ROTATE: 
            {
                float angle;
                Vector3 axis;
                angle = GetFloat();
                axis.x = GetFloat();
                axis.y = GetFloat();
                axis.z = GetFloat();
                currTransform.RotateAxis(angle, axis);
                break;
            }
            case TRANSLATE: 
            {
                Vector3 translation;
                translation.x = GetFloat();
                translation.y = GetFloat();
                translation.z = GetFloat();
                currTransform.Translate(translation);
                break;
            }
            case SCALE: 
            {
                Vector3 scale;
                scale.x = GetFloat();
                scale.y = GetFloat();
                scale.z = GetFloat();
                currTransform.SetScale(scale);
                break;
            }
            case PUSH:
                currTransform.SetDefault();
                break;
            case POP:
                currTransform.SetDefault();
                break;
            case IDENTITYAFFINE:
                currTransform.SetDefault();
                break;
            case AMBIENT: 
            {
                Color3 ambient;
                ambient.r = GetFloat();
                ambient.g = GetFloat();
                ambient.b = GetFloat();
                currMaterial.ambient.Set(ambient);
                break;
            }
            case DIFFUSE: 
            {
                Color3 diffuse;
                diffuse.r = GetFloat();
                diffuse.g = GetFloat();
                diffuse.b = GetFloat();
                currMaterial.diffuse.Set(diffuse);
                break;
            }
            case SPECULAR:
            {
                Color3 specular;
                specular.r = GetFloat();
                specular.g = GetFloat();
                specular.b = GetFloat();
                currMaterial.specular.Set(specular);
                break;
            }
            case EMISSIVE: 
            {
                Color3 emissive;
                emissive.r = GetFloat();
                emissive.g = GetFloat();
                emissive.b = GetFloat();
                currMaterial.emissive.Set(emissive);
                break;
            }
            
            case DEFAULTMATERIALS:
                currMaterial.SetDefault();
                break;
            case SPECULAREXPONENT:
                currMaterial.specularExponent = GetFloat();
                break;
            case GLOBALAMBIENT:
                ambientColor.r = GetFloat();
                ambientColor.g = GetFloat();
                ambientColor.b = GetFloat();
                break;
            case BACKGROUND:
                backgroundColor.r = GetFloat();
                backgroundColor.g = GetFloat();
                backgroundColor.b = GetFloat();
                break;
            case T_NULL:
                break; // The null token represents end-of-file
            case DEF: {
                std::string name, temp, leftBracket, rightBracket;
                std::string input;

                name = NextToken();
                
                if (WhichToken(name) != IDENT)
                {
                    std::cout << "Error: Identifier expected." << std::endl;
                    return false;
                }

                if (defObjects.find(name) != defObjects.end())
                {
                    std::cout << currLine << ": " << name;
                    std::cout << ": attempt to redefine." << std::endl;
                    return false;
                }
                
                leftBracket = NextToken();
                if (WhichToken(leftBracket) != LFTCURLY)
                {
                    std::cout << "Error: { expected." << std::endl;
                    return false;
                }

                /* Get object data */
            }
            default:  {
                switch(type) {
                    case CUBE:
                        newObject = std::make_shared<Cube>();
                        break;
                    case SPHERE:
                        newObject = std::make_shared<Sphere>();
                        break;
                    /*case TORUS:
                        newObject = new Torus;
                        break;*/
                    case TAPEREDCYLINDER:
                        newObject = std::make_shared<TaperedCylinder>();
                        ((TaperedCylinder*)newObject.get())->SetTopRadius(GetFloat());
                        ((TaperedCylinder*)newObject.get())->Generate();
                        break;
                    /*case TEAPOT:
                        newObject = new Teapot;
                        break;
                    case SQUARE:
                        newObject = new Square;
                        break;*/
                    case MESH: 
                    {
                        std::string fname = NextToken();
                        newObject = std::make_shared<Mesh3VN>(fname);
                        break;
                    }// end of case: MESH
                    default: 
                    {
                        std::cerr << "Line " << nextLine
                            << ": unknown keyword " << nextStr << std::endl;
                        return false;
                    }
                }
                
                // common things to do to all Shape
                ((SceneObject*)newObject.get())->material.Set(currMaterial);
                // load transform
                ((SceneObject*)newObject.get())->transform = this->currTransform;
                ((SceneObject*)newObject.get())->SetUniformLocations(modelMatrixLoc, matAmbientLoc, matDiffuseLoc, matSpecularLoc, matEmissiveLoc, matSpecExponentLoc);
                ((SceneObject*)newObject.get())->SetModelViewUniformLocation(modelViewMatrixLoc);
                ((SceneObject*)newObject.get())->SetBoundsModelViewUnformLocation(boundsModelViewMatrixLoc);

                camera->Attach(newObject);

                // Call the notify function on the camera to notify the new object of the camera's data
                camera->Notify();
                
                objects.push_back(newObject);
                
                return true;
            }
        }
    }
    return false;
}

void Scene::SetExportFileName(const std::string& fileName)
{
    exportFileName = fileName;
}

void Scene::Export(const std::string& fileName)
{
    std::ofstream outFile(fileName.c_str());

    outFile << "light " << light.GetPosition() << " " << light.GetColor() << std::endl;
    outFile << "globalAmbient " << ambientColor << std::endl;
    outFile << "background " << backgroundColor << std::endl;

    for (size_t i = 0; i < objects.size(); i++)
    {
        outFile << "push ";

        if (objects[i]->transform.position != Vector3(0,0,0))
            outFile << "translate " << objects[i]->transform.position   << " ";

        if (objects[i]->transform.rotation.z != 0)
            outFile << "rotate "    << objects[i]->transform.rotation.z << " 0 0 1 ";
        
        if (objects[i]->transform.rotation.y != 0)
            outFile << "rotate "    << objects[i]->transform.rotation.y << " 0 1 0 ";
        
        if (objects[i]->transform.rotation.x != 0)
            outFile << "rotate "    << objects[i]->transform.rotation.x << " 1 0 0 ";

	if (objects[i]->transform.scale != Vector3(0,0,0))
            outFile << "scale "     << objects[i]->transform.scale      << " ";
	
        outFile << "ambient "   << objects[i]->material.ambient     << " ";
        outFile << "diffuse "   << objects[i]->material.diffuse     << " ";
        outFile << "specular "  << objects[i]->material.specular    << " ";
        outFile << "emissive "  << objects[i]->material.emissive    << " ";
        outFile << "specularExponent " << objects[i]->material.specularExponent << " ";
        outFile << objects[i]->type    << " ";
        outFile << "pop" << std::endl;
    }

    // Print out the comments at the end of the file
    for (size_t i = 0; i < comments.size(); i++)
    {
        outFile << "!" << comments[i] << std::endl;
    }
    SaveCamera(fileName);
}

void Scene::SaveCamera(const std::string& fileName)
{
    std::string cameraFileName = fileName + ".camera";
    std::ofstream outFile(cameraFileName.c_str());

    GLfloat viewAngle, width, height, nearDist, farDist;
    camera->GetShape(viewAngle, width, height, nearDist, farDist);
    
    outFile << camera->backward << " "
	    << camera->right << " "
	    << camera->up << ""
	    << camera->eye << std::endl;
    outFile << viewAngle << " "
	    << width << " "
	    << height << " "
	    << nearDist << " "
	    << farDist << std::endl;
}

void Scene::LoadCamera(const std::string& fileName)
{
    GLfloat x, y, z;

    std::string cameraFileName = fileName + ".camera";
    std::ifstream infile(cameraFileName.c_str());

    if (infile)
    {
        infile >> x >> y >> z;
        Vector3 backward(x, y, z);
        infile >> x >> y >> z;
        Vector3 right(x, y, z);
        infile >> x >> y >> z;
        Vector3 up(x, y, z);
        infile >> x >> y >> z;
        Vector3 eye(x, y, z);
        GLfloat viewAngle, width, height, nearDist, farDist;
        infile >> viewAngle >> width >> height  >> nearDist >> farDist;
        camera->SetFromAxes(backward, right, up, eye);
	    camera->SetShape(viewAngle, width, height, nearDist, farDist);
    }
    else
    {
	    camera->Set(Vector3(0, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));
    }
}
void Scene::Export()
{
    std::string fileName = exportFileName;

    if (fileName == "")
    {
        fileName = "autosave_scene.txt";
    }

    Export(fileName);
}

void Scene::Insert(std::shared_ptr<SceneObject> newObject)
{
    Material  newMat;
    Transform newTransf;

    // Common things to do to all Shape
    newObject->material.Set(newMat);
    // Load transform 
    newObject->transform = newTransf;
    // Set the new object's position to be 5 units in front of the camera
    newObject->transform.SetPosition(camera->eye + (-1 * camera->backward * 5));
    newObject->boundBox->RecalculateFromTransform();

    newObject->SetUniformLocations(modelMatrixLoc, matAmbientLoc, matDiffuseLoc, matSpecularLoc, matEmissiveLoc, matSpecExponentLoc);
    newObject->SetModelViewUniformLocation(modelViewMatrixLoc);
    newObject->SetBoundsModelViewUnformLocation(boundsModelViewMatrixLoc);

    camera->Attach(newObject);

    // Call the notify function on the camera to notify the new object of the camera's data
    camera->Notify();

    objects.push_back(newObject);
}

void Scene::SetUpMainDialog()
{
    if (interface == NULL)
        return;
     
    MainDialog* mainDialog = interface->GetMainDialog();
    mainDialog->SetSceneContext(this);
    mainDialog->SetLoadCallback(ReadFunctionForwarder);
    mainDialog->SetSaveCallback(ExportFunctionForwarder);
    mainDialog->SetInsertCallback(InsertFunctionForwarder);
    mainDialog->SetAttributesPointers(&(light.GetPosition()), &(light.GetColor()), &ambientColor, &backgroundColor);
}

void Scene::SetSelectedObject(std::shared_ptr<SceneObject> obj)
{
    
    ObjectDialog* dialog = interface->GetObjectDialog();
    dialog->selectedObject = obj.get();

    selectedObject = obj;

    if (obj == NULL)
    {
        dialog->Hide();
        return;
    }

    dialog->Create();
    dialog->Refresh();
    dialog->Show();
}

void Scene::ResetRenderModes()
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        objects[i]->mesh.SetRenderMode(Mesh::MODE_SOLID);
    }
}

void Scene::DrawSelectedBounds()
{
    if (selectedObject == NULL)
        return;

    selectedObject->DrawBounds();
}

void Scene::SetCamera(Camera* cam)
{
    camera = cam;
}

void Scene::ReadFunctionForwarder(void* context, const std::string& fileName)
{
    static_cast<Scene*>(context)->ReadFile(fileName);
}

void Scene::ExportFunctionForwarder(void* context, const std::string& fileName)
{
    static_cast<Scene*>(context)->Export(fileName);
}

void Scene::InsertFunctionForwarder(void* context, std::shared_ptr<SceneObject> newObject)
{
    static_cast<Scene*>(context)->Insert(newObject);
}

void Scene::SetBackground(const Color3& color)
{
    backgroundColor.Set(color);
}

void Scene::SetModelUniformLocations(GLuint model, GLuint ambient, GLuint diffuse, GLuint specular, GLuint emissive, GLuint specExponent)
{
    modelMatrixLoc = model;
    matAmbientLoc = ambient;
    matDiffuseLoc = diffuse;
    matSpecularLoc = specular;
    matEmissiveLoc = emissive;
    matSpecExponentLoc = specExponent;
}

void Scene::SetLightUniformLocations(GLuint position, GLuint color, GLuint ambient)
{
    lightPositionLoc = position;
    lightColorLoc    = color;
    lightAmbientLoc  = ambient;
}

void Scene::SetModelViewUniformLocation(GLuint modelView)
{
    modelViewMatrixLoc = modelView;
}

void Scene::SetBoundsModelViewUnformLocation(GLuint modelView)
{
    boundsModelViewMatrixLoc = modelView;
}

void Scene::SetUpLight()
{
    Color3 color = light.GetColor();
    Vector3 position = light.GetPosition();

    glUniform3f(lightColorLoc, color.r, color.g, color.b);
    glUniform3f(lightPositionLoc, position.x, position.y, position.z);
    glUniform3f(lightAmbientLoc, ambientColor.r, ambientColor.g, ambientColor.b);
}
