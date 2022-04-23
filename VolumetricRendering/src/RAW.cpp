#include "RAW.h"

//Loading volume data and creating a texture
GLubyte* RAW::loadRaw(std::string filePath, size_t xDim, size_t yDim, size_t zDim)
{
	//https://www.eecs.umich.edu/courses/eecs380/HANDOUTS/cppBinaryFileIO-2.html
	//read file
	std::ifstream rawFile(filePath.c_str(), std::ios::binary | std::ios::in);

	GLubyte* volBytes = new GLubyte[xDim * yDim * zDim];
	//file error check
	if (rawFile.good())
	{
		rawFile.read(reinterpret_cast<char*>(volBytes), xDim * yDim * zDim * sizeof(GLubyte));
		rawFile.close();
	}
	else
	{
		std::cout << "ERROR: Raw file could not be read." << std::endl;

	}

	//Writing out the binary file to check if we read the file correctly
	/*std::ofstream outBinFile;
	outBinFile.open("../check.bin", std::ios::binary | std::ios::out);
	outBinFile.write(reinterpret_cast<char*>(volBytes), xDim * yDim * zDim * sizeof(GLubyte));
	outBinFile.close();*/

	//Generating texture for OpenGL
	std::cout << "INFO: Raw file read successfuly." << std::endl;
	return volBytes;
}