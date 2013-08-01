#ifndef GLMESH_H
#define GLMESH_H
#include "glutil.h"
#include "glm/glm.hpp"

#include <vector>


//TODO: Create a few vertex classes that can be passed into this class
template <class T>
class GLMesh
{
protected:
   GLint _vao;
   GLint _vbo;

   std::vector<T> verts;
   std::vector<GLuint> indices;


public:
  GLMesh(){};

};
#endif // GLMESH_H
