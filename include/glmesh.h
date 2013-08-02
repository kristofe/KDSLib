#ifndef GLMESH_H
#define GLMESH_H
#include "glutil.h"
#include "glm/glm.hpp"

#include <vector>


//TODO: Create a few vertex classes that can be passed into this class
template <class T>
class GLMesh
{
//Methods
public:
  GLMesh(){};

private:
  DISALLOW_COPY_AND_ASSIGN(GLMesh);

//Data Members
protected:
  GLint _vao;
  GLint _vbo;

  std::vector<T> verts;
  std::vector<GLuint> indices;
};
#endif // GLMESH_H
