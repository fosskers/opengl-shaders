#ifndef __opengl_shaders__h__
#define __opengl_shaders__h__

#include <stdio.h>
#include <GL/glew.h>

// --- //

// Totally arbitrary
#define MAX_SOURCE_LEN 10000

typedef struct shaders_t {
        GLuint vertexShader;
        GLuint fragmentShader;
} shaders_t;

/* Creates and links a complete Shader Program */
GLuint oglsProgram(shaders_t* shaders);

/* Kill compiled shader objects */
void oglsDestroy(shaders_t* shaders);

/* Compiles shaders, given File pointers to their sources */
shaders_t* oglsShaders(const char* vSource, const char* fSource);

GLuint oglsCompileShader(const GLchar* source, GLenum shaderType);

char* oglsReadShaderSource(FILE* source);

#endif
