#ifndef __opengl_shaders__h__
#define __opengl_shaders__h__

#include <stdio.h>
#include <GL/glew.h>

// --- //

// Totally arbitrary
#define MAX_SOURCE_CHARS 10000

typedef struct shaders_t {
        GLuint vertexShader;
        GLuint fragmentShader;
} shaders_t;

// --- //

/* Compiles shaders, given the filenames of their sources */
shaders_t* oglsShaders(const char* vSource, const char* fSource);

/* Creates and links a complete Shader Program */
GLuint oglsProgram(shaders_t* shaders);

/* Kill compiled shader objects */
void oglsDestroy(shaders_t* shaders);

/* Don't call these functions */
GLuint oglsCompileShader(const GLchar* source, GLenum shaderType);
char* oglsReadShaderSource(FILE* source);

#endif
