#include "Shader.h"

//Constructor: Shader Reading and Linking
Shader::Shader(const char* vertexFile, const char* fragmentFile)
{
    // Read shader files
    std::string vertexCode = readShaders(vertexFile);
    std::string fragmentCode = readShaders(fragmentFile);

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    //Vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    //Compile error check
    GLint status;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Fragment shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Compile error check
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    //Link shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //Linking errors check
    glGetProgramiv(ID, GL_LINK_STATUS, &status);
    if (!status) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    //Delete Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

//Activates the Shader Program
void Shader::shaderCall()
{
    glUseProgram(ID);
}

//https://stackoverflow.com/questions/13546461/what-does-gluseprogram0-do
void Shader::shaderClose()
{
    glUseProgram(0);
}

//Deletes the Shader Program
void Shader::shaderDestroy()
{
    glDeleteProgram(ID);
}

//Reads a text file and outputs a string with everything in the text file
std::string readShaders(const char* filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (in.good())
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

//Access shader object id
GLuint Shader::getShaderID()
{
    return ID;
}