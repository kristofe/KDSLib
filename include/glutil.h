#ifndef KDSLIB_GLUTIL_H
#define KDSLIB_GLUTIL_H

#ifdef WIN32
   #include <GL/gl.h>
#else
   #include <OpenGL/gl3.h>
#endif
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>

namespace kdslib
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

     static std::string getShaderSource(const std::string& filename);

     static GLuint loadShaders(const std::string& vsFileName,
                               const std::string& fsFileName,
                               const std::string& gsFileName);

     static std::string getOpenGLInfo();
     static int checkGLErrors();

   //private:
   //  std::map<std::string, unsigned int>		mStringToEnumDB;

   };


}

#endif // KDSLIB_GLUTIL_H
