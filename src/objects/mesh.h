#ifndef __MESH__H_
#define __MESH__H_

#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include <string>
#include <vector>
#include "vector3.h"

class Mesh
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
        Mesh(const std::vector<Vector3>& vertexVector);

        /********************
         * Public Functions *
         ********************/
        void Create(const std::vector<Vector3>& vertexVector);
        void Draw();
        void SetUpGL();
        void SetRenderMode(RenderMode m );

    private:
        /*********************
         * Private Variables *
         *********************/
        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        RenderMode mode;

        std::vector<Vector3> reducedVerts;
        std::vector<Vector3> reducedNorms;
        std::vector<GLuint>  indexVec;
        std::vector<GLfloat> reducedGLArray;

        GLuint meshVAO;
        GLuint meshVBO;
        GLuint meshEBO;

        /*********************
         * Private Functions *
         *********************/
        Vector3 CalculateFaceNormal(const Vector3& vert1, const Vector3& vert2, const Vector3& vert3);

        void GenerateNormals();
        void ReduceArrays();
        void GenerateIndexVector();
        void CreateGLArrays();

        void DrawEdges() const;
        void DrawFaces() const;
        void DrawGL()    const;
};

#endif