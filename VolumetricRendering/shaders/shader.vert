#version 460 core

layout (location = 0) in vec3 aPos;

//Uniform
uniform mat4 MVP;

//https://www.khronos.org/opengl/wiki/Type_Qualifier_(GLSL)#Interpolation_qualifiers
smooth out vec3 EntryPointCoord;
smooth out vec4 ExitPointCoord;

void main()
{
	gl_Position = MVP * vec4(aPos, 1.0);
	//coords(-0.5 to 0.5) -> texture(0,1)
	EntryPointCoord = aPos + vec3(0.5);
	ExitPointCoord = MVP * vec4(EntryPointCoord, 1.0);
}