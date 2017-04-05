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
        /***************
         * Constructor *
         ***************/
        Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	/********************
         * Public Functions *
         ********************/
        void Use();
        GLuint GetProgram();
    
    private:
	/********************
         * Private Function *
         ********************/
        GLuint SetUpShader(const GLchar* source, std::string shaderType);

	/********************
         * Private Variable *
         ********************/
        GLuint program;
};

#endif
