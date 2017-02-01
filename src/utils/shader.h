#ifndef __SHADER_H_
#define __SHADER_H_

// Included to get all of the required OpenGL headers
#ifndef __gl_h_
    #include <glad/glad.h>
#endif
#include <string>

class Shader
{
    public: 
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
        void Use();
        GLuint GetProgram();
    
    private:
        // Prevent the creation of instances of this object
        

        GLuint SetUpShader(const GLchar* source, std::string shaderType);
        GLuint program;
};

#endif