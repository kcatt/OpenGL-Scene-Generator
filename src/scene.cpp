#include "scene.h"
#include <cstdlib>
#include <iostream>

Scene::Scene() {
    currMaterial.SetDefault();
    background.Set(.8,.3,0.6f);
    ambient.Set(0.1f,0.1f,0.1f);
    minReflectivity = 0.5;
    minTransparency = 0.5;
    maxRecursionDepth = 3;
}

Scene::Scene(const std::string& fileName) {
    Scene();
    Read(fileName);
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
                if (lastchar == 0) 
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
                    if (lastChar == 0  
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

void Scene::GetFloat(void)
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

void Scene::IsIdentifier(const std::string& keyword)
{
    if (!isalpha(keyword[0]))
        return false;
    
    for (int count = 1; cout < keyword.length(); count++)
    {
        if ((!isalnum(keyword[count])) && (temp[count] != '.'))
            return false;
    }

    return true;
}

void Scene::ReadFile(const std::string& fileName)
{
    inFile = std::make_unique<ifstream>(fileName.c_str());

    if (!(*inFile))
    {
        std::cout << "Cannot find or open file: " << fileName << std::endl;
        return false;
    }

    fileStream = std::make_unique<stringstream>();
    currLine = nextLine = 1;
    char nextChar;
    FreeScene();

    // Read the whole file
    while (inFile->get(ch)) 
    {
        *fileStream << ch;
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
    for (int i = 0; i < obj.size(); i++)
        obj[i]->Draw();
}

bool Scene::GetObject(void)
{
    std::string  nextStr;
    SceneObject *newObject;
    mTokenType   type;

    while ((typ = (whichtoken(s = nexttoken()))) != T_NULL) {
        switch(typ) {
            case LIGHT: 
            {
                Point3 p;
                Color3 c;
                p.x = getFloat();
                p.y = getFloat();
                p.z = getFloat();
                c.red = getFloat();
                c.green = getFloat();
                c.blue = getFloat();
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
                angle = getFloat();
                u.x = getFloat();
                u.y = getFloat();
                u.z = getFloat();
                affStk.rotate(angle,u);
                break;
            }
            case TRANSLATE: 
            {
                Vector3 d;
                d.x = getFloat();
                d.y = getFloat();
                d.z = getFloat();
                affStk.translate(d);
                break;
            }
            case SCALE: 
            {
                float sx, sy, sz;
                sx = getFloat();
                sy = getFloat();
                sz = getFloat();
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
                dr = getFloat();
                dg = getFloat();
                db = getFloat();
                currMtrl.ambient.Set(dr,dg,db);
                break;
            }
            case DIFFUSE: 
            {
                float dr,dg,db;
                dr = getFloat();
                dg = getFloat();
                db = getFloat();
                currMtrl.diffuse.Set(dr,dg,db);
                break;
            }
            case SPECULAR:
            {
                float dr,dg,db;
                dr = getFloat();
                dg = getFloat();
                db = getFloat();
                currMtrl.specular.Set(dr,dg,db);
                break;
            }
            case EMISSIVE: 
            {
                float dr,dg,db;
                dr = getFloat();
                dg = getFloat();
                db = getFloat();
                currMtrl.emissive.Set(dr,dg,db);
                break;
            }
            case PARAMETERS: 
            {
                currMtrl.numParams = (int)getFloat();
                for(int i = 0; i < currMtrl.numParams; i++)
                    currMtrl.params[i] = getFloat();
                break;
            }
            case SPECULARFRACTION:
                currMtrl.specularFraction = getFloat();
                break;
            case SURFACEROUGHNESS:
                currMtrl.surfaceRoughness = getFloat();
                break;
            case DEFAULTMATERIALS:
                currMtrl.setDefault();
                break;
            case SPEEDOFLIGHT:
                currMtrl.speedOfLight = getFloat();
                break;
            case SPECULAREXPONENT:
                currMtrl.specularExponent = getFloat();
                break;
            case TRANSPARENCY:
                currMtrl.transparency = getFloat();
                break;
            case REFLECTIVITY:
                currMtrl.reflectivity = getFloat();
                break;
            case GLOBALAMBIENT:
                ambient.r = getFloat();
                ambient.g = getFloat();
                ambient.b = getFloat();
                break;
            case BACKGROUND:
                background.r = getFloat();
                background.g = getFloat();
                background.b = getFloat();
                break;
            case MINREFLECTIVITY:
                minReflectivity = getFloat();
                break;
            case MINTRANSPARENCY:
                minTransparency = getFloat();
                break;
            case MAXRECURSIONDEPTH:
                maxRecursionDepth = getFloat();
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
                        ((TaperedCylinder*)newShape)->smallRadius = getFloat();
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
                    }// end of case: MESH*/
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
                
                obj.push_back(newObject);
                
                return true;
            }
        }
    }
    return false;
}

void Scene::SetBackground(const Color3& color)
{
    background.set(color);
}