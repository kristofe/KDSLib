#ifndef KDSLIB_GLUTIL_H
#define KDSLIB_GLUTIL_H

#ifdef WIN32
   #include <GL/gl.h>
#else
   #include <OpenGL/gl.h>
#endif
#include <string>
#include <iostream>
#include <fstream>

namespace KDSlib
{

   class GLUtil
   {
   public:
     GLUtil();
     static GLuint buildShader(const std::string& name,
                               const std::string& source, GLenum shaderType);

     static GLuint buildProgram(const std::string& vsSource,
                                const std::string& fsSource,
                                const std::string& gsSource);

     static std::string getShaderSource(const char *filename);

     static GLuint loadShaders(const char* vsFileName,
                               const char* fsFileName, const char* gsFileName);


   };


}

#endif // KDSLIB_GLUTIL_H
