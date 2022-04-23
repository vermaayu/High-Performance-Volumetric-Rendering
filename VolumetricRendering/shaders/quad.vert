#version 460 core
// Input from layout
layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec3 aColors;

out vec3 color;

//Model, View, Perspective uniform
uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(aPos, 1.0);

	//For the fragment shader
	color = aPos + vec3(0.5);
}
