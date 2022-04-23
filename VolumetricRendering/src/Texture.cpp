#include "Texture.h"

//Transfer function texture
GLuint Texture::textureTransferFunction(float transfer[])
{
	GLuint transferTexture;
	glGenTextures(1, &transferTexture);
	glBindTexture(GL_TEXTURE_1D, transferTexture);

	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, 256, 0, GL_RGBA, GL_FLOAT, transfer);

	std::cout << "INFO: Transfer function loaded." << std::endl;
	return transferTexture;
}

//Quad Texture
GLuint Texture::textureQuad(int width, int height)
{
	GLuint quadTexture;
	glGenTextures(1, &quadTexture);
	glBindTexture(GL_TEXTURE_2D, quadTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

	std::cout << "INFO: Quad texture loaded." << std::endl;
	return quadTexture;
}

//Volume Texture
GLuint Texture::textureVolume(GLubyte* data, size_t xDim, size_t yDim, size_t zDim)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_3D, textureID);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage3D.xhtml
	glTexImage3D(GL_TEXTURE_3D, 0, GL_R8, xDim, yDim, zDim, 0, GL_RED, GL_UNSIGNED_BYTE, (GLvoid*)data);

	delete[]data;

	std::cout << "INFO: Volume texture loaded." << std::endl;
	return textureID;
}