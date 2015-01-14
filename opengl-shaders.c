#include <stdlib.h>

#include "opengl-shaders.h"
#include "dbg.h"

// --- //

/* Creates and links a complete Shader Program */
GLuint oglsProgram(shaders_t* shaders) {
        GLuint program = -1;

        check(shaders != NULL, "Bad shaders given.");

        // Link shaders
        program = glCreateProgram();
        glAttachShader(program,shaders->vertexShader);
        glAttachShader(program,shaders->fragmentShader);
        glLinkProgram(program);

        return program;
 error:
        return -1;
}

/* Kill compiled shader objects */
void oglsDestroy(shaders_t* shaders) {
        if(shaders != NULL) {
                glDeleteShader(shaders->vertexShader);
                glDeleteShader(shaders->fragmentShader);
                free(shaders);
        }
}

/* Compiles shaders, given the filenames of their sources */
shaders_t* oglsShaders(const char* vSourceFile, const char* fSourceFile) {
        GLuint vShader;
        GLuint fShader;
        shaders_t* shaders = NULL;
        FILE* vSource = NULL;
        FILE* fSource = NULL;
        
        vSource = fopen(vSourceFile, "r");
        fSource = fopen(fSourceFile, "r");
        
        GLchar* vertexSource   = oglsReadShaderSource(vSource);
        GLchar* fragmentSource = oglsReadShaderSource(fSource);
        
        check(vertexSource != NULL && fragmentSource != NULL,
              "Shader source files weren't read properly.");

        vShader = oglsCompileShader(vertexSource,   GL_VERTEX_SHADER);
        fShader = oglsCompileShader(fragmentSource, GL_FRAGMENT_SHADER);

        check(vShader != -1 && fShader != -1, "Shader compilation failed.");

        shaders = malloc(sizeof(shaders_t));
        check_mem(shaders);
        shaders->vertexShader   = vShader;
        shaders->fragmentShader = fShader;

 error:
        // Free allocated space and close files, if we can.
        if(vertexSource != NULL)   { free(vertexSource);   }
        if(fragmentSource != NULL) { free(fragmentSource); }
        if(vSource != NULL)        { fclose(vSource);      }
        if(fSource != NULL)        { fclose(fSource);      }

        return shaders;
}

GLuint oglsCompileShader(const GLchar* source, GLenum shaderType) {
        GLchar infoLog[512];
        GLint  success;
        GLuint shader = -1;

        check(source != NULL, "Empty shader source given.");

        shader = glCreateShader(shaderType);        
        glShaderSource(shader,1,&source,NULL);
        glCompileShader(shader);

        // Check for compilation success.
        glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        check(success, "Shader failed to compile:\n%s\n", infoLog);

        return shader;
 error:
        return -1;
}

GLchar* oglsReadShaderSource(FILE* source) {
        GLchar* s = NULL;
        char c;
        int i = 0;
        
        check(source != NULL, "NULL shader source file given.");
        
        s = malloc(sizeof(GLchar) * MAX_SOURCE_CHARS);
        check_mem(s);

        while((c = fgetc(source)) != EOF && i < MAX_SOURCE_CHARS - 1) {
                s[i] = c;
                i++;
        }

        s[i+1] = '\0';

 error:
        return s;
}
