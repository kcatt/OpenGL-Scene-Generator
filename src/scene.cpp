#include "scene.h"
#include <cstdlib>
#include <iostream>

Scene::Scene() {
    currMaterial.SetDefault();
    backgroundColor.Set(.8,.3,0.6f);
    ambientColor.Set(0.1f,0.1f,0.1f);
    minReflectivity = 0.5;
    minTransparency = 0.5;
    maxRecursionDepth = 3;
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
            case '!': {
                // This is a comment. Read the rest of the line and discard
                while (nextChar != '\n' && fileStream->get(nextChar));
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
}

// Clear the vectors in the scene
void Scene::FreeScene(void)
{
    objects.clear();
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
    inFile = std::make_unique<std::ifstream>(fileName.c_str());

    if (!(*inFile))
    {
        std::cout << "Cannot find or open file: " << fileName << std::endl;
        return false;
    }

    fileStream = std::make_unique<std::stringstream>();
    currLine = nextLine = 1;
    char nextChar;
    FreeScene();

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
     if (keyword == "makePixmap")
        return MAKEPIXMAP;
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
    if (keyword == "specularFraction")
        return SPECULARFRACTION;
    if (keyword == "surfaceRoughness")
        return SURFACEROUGHNESS;
    if (keyword == "emissive")
        return EMISSIVE;
    if (keyword == "specularExponent")
        return SPECULAREXPONENT;
    if (keyword == "speedOfLight")
        return SPEEDOFLIGHT;
    if (keyword == "transparency")
        return TRANSPARENCY;
    if (keyword == "reflectivity")
        return REFLECTIVITY;
    if (keyword == "parameters")
        return PARAMETERS;
    if (keyword == "texture")
        return TEXTURE;
    if (keyword == "globalAmbient")
        return GLOBALAMBIENT;
    if (keyword == "minReflectivity")
        return MINREFLECTIVITY;
    if (keyword == "minTransparency")
        return MINTRANSPARENCY;
    if (keyword == "maxRecursionDepth")
        return MAXRECURSIONDEPTH;
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
    for (size_t i = 0; i < objects.size(); i++)
        objects[i]->Draw();
}

bool Scene::GetObject(void)
{
    std::string  nextStr;
    SceneObject *newObject;
    mTokenType   type;

    /*while ((typ = (whichtoken(s = nexttoken()))) != T_NULL) {
        switch(typ) {
            /*case LIGHT: 
            {
                Point3 p;
                Color3 c;
                p.x = GetFloat();
                p.y = GetFloat();
                p.z = GetFloat();
                c.red = GetFloat();
                c.green = GetFloat();
                c.blue = GetFloat();
                Light l;
                l.setPosition(p);
                l.setColor(c);
                light.insert(light.begin(), l);
                break;
            }
            case ROTATE: 
            {
                float angle;
                Vector3 u;
                angle = GetFloat();
                u.x = GetFloat();
                u.y = GetFloat();
                u.z = GetFloat();
                affStk.rotate(angle,u);
                break;
            }
            case TRANSLATE: 
            {
                Vector3 d;
                d.x = GetFloat();
                d.y = GetFloat();
                d.z = GetFloat();
                affStk.translate(d);
                break;
            }
            case SCALE: 
            {
                float sx, sy, sz;
                sx = GetFloat();
                sy = GetFloat();
                sz = GetFloat();
                affStk.scale(sx, sy, sz);
                break;
            }
            case PUSH:
                affStk.duplicate();
                break;
            case POP:
                affStk.popAndDrop();
                break;
            case IDENTITYAFFINE:
                affStk.setIdentity();
                break;
            case AMBIENT: 
            {
                float dr, dg, db;
                dr = GetFloat();
                dg = GetFloat();
                db = GetFloat();
                currMtrl.ambient.Set(dr,dg,db);
                break;
            }
            case DIFFUSE: 
            {
                float dr,dg,db;
                dr = GetFloat();
                dg = GetFloat();
                db = GetFloat();
                currMtrl.diffuse.Set(dr,dg,db);
                break;
            }
            case SPECULAR:
            {
                float dr,dg,db;
                dr = GetFloat();
                dg = GetFloat();
                db = GetFloat();
                currMtrl.specular.Set(dr,dg,db);
                break;
            }
            case EMISSIVE: 
            {
                float dr,dg,db;
                dr = GetFloat();
                dg = GetFloat();
                db = GetFloat();
                currMtrl.emissive.Set(dr,dg,db);
                break;
            }
            case PARAMETERS: 
            {
                currMtrl.numParams = (int)GetFloat();
                for(int i = 0; i < currMtrl.numParams; i++)
                    currMtrl.params[i] = GetFloat();
                break;
            }
            case SPECULARFRACTION:
                currMtrl.specularFraction = GetFloat();
                break;
            case SURFACEROUGHNESS:
                currMtrl.surfaceRoughness = GetFloat();
                break;
            case DEFAULTMATERIALS:
                currMtrl.setDefault();
                break;
            case SPEEDOFLIGHT:
                currMtrl.speedOfLight = GetFloat();
                break;
            case SPECULAREXPONENT:
                currMtrl.specularExponent = GetFloat();
                break;
            case TRANSPARENCY:
                currMtrl.transparency = GetFloat();
                break;
            case REFLECTIVITY:
                currMtrl.reflectivity = GetFloat();
                break;
            case GLOBALAMBIENT:
                ambient.r = GetFloat();
                ambient.g = GetFloat();
                ambient.b = GetFloat();
                break;
            case BACKGROUND:
                background.r = GetFloat();
                background.g = GetFloat();
                background.b = GetFloat();
                break;
            case MINREFLECTIVITY:
                minReflectivity = GetFloat();
                break;
            case MINTRANSPARENCY:
                minTransparency = GetFloat();
                break;
            case MAXRECURSIONDEPTH:
                maxRecursionDepth = GetFloat();
                break;
            case T_NULL:
                break; // The null token represents end-of-file
            default:  {
                switch(typ) {
                    case CUBE:
                        newShape = new Cube;
                        break;
                    case SPHERE:
                        newShape = new Sphere;
                        break;
                    /*case TORUS:
                        newShape = new Torus;
                        break;
                    case TAPEREDCYLINDER:
                        newShape = new TaperedCylinder;
                        ((TaperedCylinder*)newShape)->smallRadius = GetFloat();
                        break;
                    case TEAPOT:
                        newShape = new Teapot;
                        break;
                    case SQUARE:
                        newShape = new Square;
                        break;
                    case MESH: 
                    {
                        string fname = nexttoken();
                        newShape = new Mesh(fname);
                        break;
                    }// end of case: MESH
                    default: 
                    {
                        cerr << "Line " << nextline
                            << ": unknown keyword " << s << endl;
                        return false;
                    }
                }
                // common things to do to all Shape
                ((SceneObject*)newShape)->mat.set(currMtrl);
                // load transform and its inverse
                ((SceneObject*)newShape)->transform = this->currTransform;
                ((SceneObject*)newShape)->transf.set(affStk.tos[0].affn);
                ((SceneObject*)newShape)->invTransf.set(affStk.tos[0].invAffn);
                ((SceneObject*)newShape)->SetModelMatrixLoc(modelMatrixLoc);
                
                obj.push_back(newObject);
                
                return true;
            }
        }
    }*/
    return false;
}

void Scene::SetBackground(const Color3& color)
{
    backgroundColor.Set(color);
}

void Scene::SetModelMatrixLoc(GLuint location)
{
    modelMatrixLoc = location;
}