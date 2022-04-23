#version 460 core


smooth in vec3 EntryPointCoord;
smooth in vec4 ExitPointCoord;

//Uniforms
uniform sampler2D QuadTex;
uniform sampler3D VolumeTex;
uniform sampler1D TransferFuncTex;  
uniform float     stepSize;
uniform vec2      screenSize;

//Output vector
layout (location = 0) out vec4 FragColor;

//Minimum and Maximum texture coordinates
const vec3 minTexture = vec3(0);
const vec3 maxTexture = vec3(1);	

const int MAX_SAMPLES = 300;

void main()
{
	//Texturing Exit Points
    vec3 exitTex = texture(QuadTex, gl_FragCoord.st/screenSize).xyz;

	//Direction for the ray
   vec3 direc = normalize(exitTex - EntryPointCoord); 

   //Direction with stepsize magnitude for the ray
   vec3 dirStep = direc * stepSize; 

   //Handle to check out of bound
   bool stop = false; 

   vec3 dataPos = EntryPointCoord;

   for (int i = 0; i < MAX_SAMPLES; i++) {

		dataPos = dataPos - dirStep;
		
		//To check if the ray is out of the bounding box
		stop = dot(sign(dataPos-minTexture),sign(maxTexture-dataPos)) < 3.0;
		if (stop)
		{
			//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			break;
		}
			
		//Sampling
		float sampleVol = texture(VolumeTex, dataPos).r;	
		vec4 sampleTF = texture(TransferFuncTex, sampleVol);
		
		//Summing the intensity and colour for the ray
		float previousAlpha = sampleVol - (sampleVol * FragColor.a);
		FragColor.rgb = previousAlpha * vec3(sampleTF) + FragColor.rgb; 
		FragColor.a += previousAlpha; 

		//Uncomment for without transfer function
		//float previousAlpha = sampleVol - (sampleVol * FragColor.a);
		//FragColor.rgb = previousAlpha * vec3(sampleVol) + FragColor.rgb; 
		//FragColor.a += previousAlpha; 
		
		//Max intensity = 1 (approx) reached
		if( FragColor.a>0.9)
			break;
	} 

	//Back and Front face render
    // FragColor = vec4(EntryPointCoord, 1.0);
    // FragColor = vec4(exitTex, 1.0);
}