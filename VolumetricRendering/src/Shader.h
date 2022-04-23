#pragma once

#include <GL/glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

//Read shaders
std::string readShaders(const char* filename);

class Shader
{
private:
	//Shader object ID
	GLuint ID;

	//Shader program object reference 
	GLuint fragmentShader, vertexShader;

public:

	//Constructor
	Shader(const char* vertexFile, const char* fragmentFile);

	//Activates the Shader Program
	void shaderCall();

	//Deactivates the Shader Program
	void shaderClose();

	//Deletes the Shader Program
	void shaderDestroy();

	//Access shader object ID
	GLuint getShaderID();
};