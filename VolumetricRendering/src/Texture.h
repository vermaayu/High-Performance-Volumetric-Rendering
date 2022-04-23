#pragma once

#include <GL/glew.h>
#include <iostream>

//All textures
class Texture
{
public:

	//Transfer function texture
	static GLuint textureTransferFunction(float transfer[]);

	//Quad Texture
	static GLuint textureQuad(int width, int height);

	//Volume Texture
	static GLuint textureVolume(GLubyte* data, size_t xDim, size_t yDim, size_t zDim);
};