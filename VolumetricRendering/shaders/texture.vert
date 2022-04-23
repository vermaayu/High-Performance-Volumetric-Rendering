#version 330 core
  
layout(location = 0) in vec3 aPos;

//uniform
uniform mat4 transform;

//Smooth interpolates the texture values for the fragment shader outputs
smooth out vec3 vUV;

void main()
{  
	gl_Position = transform * vec4(aPos, 1.0);

	//Normalising texture coordinates by adding (0.5,0.5,0.5) to the object coordinates and bring it between (0,0,0) and (1,1,1)
	vUV = aPos + vec3(0.5);
}