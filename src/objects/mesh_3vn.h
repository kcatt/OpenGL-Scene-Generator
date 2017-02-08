#ifndef __MESH_3VN__H_
#define __MESH_3VN__H_

#include <vector>
#include "scene_object.h"
#include "vector3.h"

class Mesh3VN : public SceneObject
{
    public:
        /****************
         * Constructors *
         ****************/
        Mesh3VN();
        Mesh3VN(const std::string & file);

        /**************
         * Destructor *
         **************/
        ~Mesh3VN();

        /********************
         * Public Functions *
         ********************/
        void DrawEdges();
        void DrawFaces();
        void Draw();
        void Free();
        bool IsEmpty();
        void MakeEmpty();
        void ReadMesh(const std::string & file);

        /*******************
         * Public Variable *
         *******************/
        std::string fileName;

    private:
        /**************************
         * Class Specific Structs *
         **************************/
        struct VertexID {
            int vertIndex;
            int normIndex;
        };

        struct Face {
            VertexID vert[3]; // An array of vertex and normal indices
        };

        /*********************
         * Private Variables *
         *********************/
        int        lastVertUsed;
        int        lastNormUsed;
        int        lastFaceUsed;
        size_t     numVerts;
        size_t     numNorms;
        size_t     numFaces;
        Vector3   *points;
        Vector3   *normals;
        std::vector<Face> faces;

        /*********************
         * Private Functions *
         *********************/
        void SetUpMesh();
};

#endif