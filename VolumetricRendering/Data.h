#pragma once

/*------------------------------------------------------------------ Headers -----------------------------------------------*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

/*--------------------------------------------------------- Function Declarations --------------------------------------*/

//Definitions in VolumetricRendering.cpp
void setUniform();
void uiRoutine();
void transformationRoutine(GLenum glFaces, GLuint ID);

/*--------------------------------------------------------- Data Variables/Constants --------------------------------------*/

//Window Context
GLFWwindow* window;

//ImGui states and control parameters (GUI)
bool show_demo_window = false;
bool wireframe = false;
bool depthTest = true;

// Transform parameters (GUI)
static float fx = 0.0f, fy = 0.0f, fz = 0.0f, scale = 1.0f;

//Buffer objects
GLuint VBO[1], VAO, EBO;

//Model-View-Perspective Matrix
glm::mat4 MVP;

//Shader ID
GLuint volShaderID;
GLuint quadShaderID;

//Texture Objects
GLuint transferFnTexObj;
GLuint quadTexObj;
GLuint volTexObj;

//StepSize
glm::vec3 stepSize = glm::vec3(1.0f/255.0f);

//Camera Position
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 2.0f);


//Vertices for bounding box
float cubeVertices[] =
{
    // front
    -0.5, -0.5,  0.5,
     0.5, -0.5,  0.5,
     0.5,  0.5,  0.5,
    -0.5,  0.5,  0.5,
    // back
    -0.5, -0.5, -0.5,
     0.5, -0.5, -0.5,
     0.5,  0.5, -0.5,
    -0.5,  0.5, -0.5
};

int cubeIndices[] =
{
    1, 5, 4,
    4, 0, 1,
    3, 7, 6,
    6, 2, 3,
    3, 0, 4,
    4, 7, 3,
    1, 2, 6,
    6, 5, 1,
    4, 5, 6,
    6, 7, 4,
    1, 0, 3,
    3, 2, 1
};

float transferFunction[] = {
    1.0f, 1.0f, 1.0f, 0.0f / 12.0f,
    0.0f, 0.0f, 1.0f, 1.0f / 12.0f,
    0.0f, 1.0f, 1.0f, 2.0f / 12.0f,
    0.0f, 1.0f, 0.0f, 3.0f / 12.0f,
    1.0f, 1.0f, 0.0f, 4.0f / 12.0f,
    1.0f, 0.0f, 0.0f, 5.0f / 12.0f,
    0.878431f, 0.0f, 1.0f, 0.5f
};