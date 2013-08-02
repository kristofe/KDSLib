#ifndef VERTEX_H
#define VERTEX_H
#include "utils.h"
#include "glm/glm.hpp"

class Vertex
{
//Methods
public:
   Vertex():_vertexStrideInFloats(16),_vertexStrideInBytes(16*sizeof(float))
   {

   }

   int getStrideInBytes(){ return sizeof(float)*16; }

private:
   DISALLOW_COPY_AND_ASSIGN(Vertex);

//Data Members
public:
   //TODO: Make sure glm::vec3 is actually using full floats.
   glm::vec3 _position;
   glm::vec3 _normal;
   glm::vec3 _uv;
   glm::vec3 _uv2;
   glm::vec4 _color;





};
#endif // VERTEX_H
