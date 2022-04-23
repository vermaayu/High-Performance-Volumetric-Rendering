#pragma once

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <cassert>

//Class to load volume data
class RAW
{
public:
	//Volume .raw file path
	//http://klacansky.com/open-scivis-datasets/metadata/bonsai.nhdr
	std::string filePath = "../Assets/bonsai_256x256x256_uint8.raw";
	//std::string filePath = "../Assets/skull_256x256x256_uint8.raw"; 

	//Dimensions as specified in the file
	size_t xDim = 256;
	size_t yDim = 256;
	size_t zDim = 256;

	//Loading volume data and creating a texture
	GLubyte* loadRaw(std::string filePath, size_t xDim, size_t yDim, size_t zDim);
};