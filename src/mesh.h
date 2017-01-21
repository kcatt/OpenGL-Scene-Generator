#ifndef __MESH__H_
#define __MESH__H_

#include <GL/glew.h>
#include <string>
#include <vector>
#include "scene_object.h"
#include "vector3.h"

// Forward declared classes
class Face;

class VertexID 
{
    // Declare Face class a friend so it can access the constructor
    friend class Face;

    public:
        /********************
         * Public Variables *
         ********************/
        size_t vertIndex;
        size_t normIndex;

    private:
        /* Make the constructor private to prevent it from being *
         * created by anyone that isn't friended. */
        VertexID();
};

class Face 
{
    public:
        /***************
         * Constructor *
         ***************/
        Face();

        /**************
         * Destructor *
         **************/
        ~Face();

        /********************
         * Public Variables *
         ********************/
        size_t numVerts;
        VertexID* vert;
};

class Mesh : public SceneObject
{
    public:
        enum RenderMode
        {
            MODE_WIRE = 0,
            MODE_SOLID,
            MODE_WIRE_SOLID
        };

        /****************
         * Constructors *
         ****************/
        Mesh();
        Mesh(const std::string & fileName);
        Mesh(const std::vector<Vector3>& vertexVector);

        /********************
         * Public Functions *
         ********************/
        void    DrawEdges() const;
        void    DrawFaces() const;
        void    Draw();
        void    SetUpGL();
        void    FreeMesh();
        bool    IsEmpty()   const;
        void    MakeEmpty();
        void    ReadMesh(const std::string& fileName);
        void    SetRenderMode(RenderMode m );
        Vector3 Newell4(int indx[]);

        /*******************
         * Public Variable *
         *******************/
        std::string fileName;

    private:
        /*********************
         * Private Variables *
         *********************/
        size_t numVerts, numNorms, numFaces;
        std::vector<Vector3>   vertices;
        std::vector<Vector3>   normals;
        Face*      faces;
        RenderMode mode;

        std::vector<Vector3> reducedVerts;
        std::vector<Vector3> reducedNorms;
        std::vector<GLuint>  indexVec;
        std::vector<GLfloat> reducedGLArray;
        GLfloat*   vertexArr;
        GLuint*    indexArr;

        GLuint meshVAO;
        GLuint meshVBO;
        GLuint meshEBO;

        /*********************
         * Private Functions *
         *********************/
        void GenerateNormals();
        void ReduceArrays();
        void GenerateIndexVector();
        void CreateGLArrays();
};

#endif