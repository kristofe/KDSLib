#include "include/glutil.h"


using namespace KDSlib;

GLUtil::GLUtil()
{
}

GLuint GLUtil::loadShaders(const char* vsFileName,
                   const char* fsFileName,
                   const char* gsFileName)
{

    std::string vsSource = getShaderSource(vsFileName);
    std::string fsSource = getShaderSource(fsFileName);
    if(gsFileName != NULL)
    {
       std::string gsSource = getShaderSource(gsFileName);
       return buildProgram(vsSource,fsSource, gsSource);
    }
    else
    {
       return buildProgram(vsSource,fsSource,NULL);
    }


}

GLuint GLUtil::buildShader(const std::string& name,
                   const std::string& source,
                   GLenum shaderType)
{
    const char* src = source.c_str();
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle,1, &src, 0);
    glCompileShader(shaderHandle);

    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);

    if(compileSuccess == GL_FALSE)
    {
        printf("Error(s) in shader %s:\n", name.c_str());
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle,sizeof(messages), 0, &messages[0]);
        printf("%s\n",messages);
        exit(1);
    }
    else
    {
        printf("Successfully created shader %s!\n", name.c_str());
    }
    return shaderHandle;
}


GLuint GLUtil::buildProgram(const std::string& vsSource,
                            const std::string& fsSource,
                            const std::string& gsSource)
{
    GLuint vertexShader = buildShader("vertex shader",vsSource,
                                      GL_VERTEX_SHADER);
    GLuint fragmentShader = buildShader("fragment shader",fsSource,
                                       GL_FRAGMENT_SHADER);

    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);

    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if(linkSuccess == GL_FALSE)
    {
        printf("Error(s) in program:\n");
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        printf("%s\n", messages);
        exit(1);
    }
    else
    {
        printf("Successfully created vertexprogram!\n");
    }
    return programHandle;
}

std::string GLUtil::getShaderSource(const char *filename)
{
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  return "";
}

/*

void drawQuadVBO() {
    glUniform1f(blendSlot, blendStrength);
    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(uvSlot);
    glUniform1i(samplerSlot,0);

    glUniform1iv(redMapSlot,sizeof(mapR),mapR);
    glUniform1iv(greenMapSlot,sizeof(mapG),mapG);
    glUniform1iv(blueMapSlot,sizeof(mapB),mapB);

    glUniform4fv(flareColor1Slot,1,flareColor1);
    glUniform2fv(dxdy1Slot,1,dxdy1);
    glUniform3fv(scale1Slot,1,scale1);

    glUniform4fv(flareColor2Slot,1,flareColor2);
    glUniform2fv(dxdy2Slot,1,dxdy2);
    glUniform3fv(scale2Slot,1,scale2);

    printf("imageDims(%3.2f,%3.2f)\n", imageDims[0],imageDims[1]);
    glUniform2fv(imageDimensionsSlot,1,imageDims);

    glBindBuffer(GL_ARRAY_BUFFER, vboQuad);

    glUniformMatrix4fv(projectionUniformSlot, 1, 0, projectionMatrix);
    glUniformMatrix4fv(modelViewUniformSlot, 1, 0, modelviewMatrix);
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, sizeof(V2fT2f),
                          BUFFER_OFFSET(0));
    glVertexAttribPointer(uvSlot, 2, GL_FLOAT, GL_FALSE, sizeof(V2fT2f),
                          BUFFER_OFFSET(sizeof(float)*2));



    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboQuadIndices);
    glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);

    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(uvSlot);

}
*/



/*
void bindFBO(GLuint fboID,Image* fboImage) {
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, fboID);
    glViewport(0, 0, fboImage->wide*fboImage->s, fboImage->high*fboImage->t);
    // The entire framebuffer won't be written to if the image was padded to POT.
    // In this case, clearing is a performance win on TBDR systems.
    glClear(GL_COLOR_BUFFER_BIT);
    glDisable(GL_BLEND);
    glViewport(0, 0, fboImage->wide, fboImage->high);
}

void restoreSystemFBO() {
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, SystemFBO);
}

void drawQuadArray() {
    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUniform1f(blendSlot, blendStrength);
    glUniformMatrix4fv(projectionUniformSlot, 1, 0, projectionMatrix);
    glUniformMatrix4fv(modelViewUniformSlot, 1, 0, modelviewMatrix);
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, sizeof(V2fT2f),  &flipquad[0].x);
    glVertexAttribPointer(uvSlot, 2, GL_FLOAT, GL_FALSE, sizeof(V2fT2f),  &flipquad[0].s);
    glUniform1i(samplerSlot,0);
    glUniform1iv(redMapSlot,sizeof(mapR),mapR);
    glUniform1iv(greenMapSlot,sizeof(mapG),mapG);
    glUniform1iv(blueMapSlot,sizeof(mapB),mapB);

    glUniform4fv(flareColor1Slot,1,flareColor1);
    glUniform2fv(dxdy1Slot,1,dxdy1);
    glUniform3fv(scale1Slot,1,scale1);

    glUniform4fv(flareColor2Slot,1,flareColor2);
    glUniform2fv(dxdy2Slot,1,dxdy2);
    glUniform3fv(scale2Slot,1,scale2);

    glUniform2fv(imageDimensionsSlot,1,imageDims);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
*/
/*
//////////////////////////////
inline void drawCube(Vector3f &p1, Vector3f &p2) {

glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y,  p2.z);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( p2.x, p1.y,  p2.z);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( p2.x,  p2.y,  p2.z);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p1.x,  p2.y,  p2.z);	// Top Left Of The Texture and Quad
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(p1.x,  p2.y, p1.z);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( p2.x,  p2.y, p1.z);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( p2.x, p1.y, p1.z);	// Bottom Left Of The Texture and Quad
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p1.x,  p2.y, p1.z);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x,  p2.y,  p2.z);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f( p2.x,  p2.y,  p2.z);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( p2.x,  p2.y, p1.z);	// Top Right Of The Texture and Quad
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(p1.x, p1.y, p1.z);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( p2.x, p1.y, p1.z);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( p2.x, p1.y,  p2.z);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(p1.x, p1.y,  p2.z);	// Bottom Right Of The Texture and Quad
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( p2.x, p1.y, p1.z);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f( p2.x,  p2.y, p1.z);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f( p2.x,  p2.y,  p2.z);	// Top Left Of The Texture and Quad
		glTexCoord2f(0.0f, 0.0f); glVertex3f( p2.x, p1.y,  p2.z);	// Bottom Left Of The Texture and Quad
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(p1.x, p1.y, p1.z);	// Bottom Left Of The Texture and Quad
		glTexCoord2f(1.0f, 0.0f); glVertex3f(p1.x, p1.y,  p2.z);	// Bottom Right Of The Texture and Quad
		glTexCoord2f(1.0f, 1.0f); glVertex3f(p1.x,  p2.y,  p2.z);	// Top Right Of The Texture and Quad
		glTexCoord2f(0.0f, 1.0f); glVertex3f(p1.x,  p2.y, p1.z);	// Top Left Of The Texture and Quad
	glEnd();

}
*/
