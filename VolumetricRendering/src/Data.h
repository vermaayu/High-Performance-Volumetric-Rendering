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

GLuint quadTexture(int width, int height);
GLuint tranferFuncTexture(float transfer[]);
void setUniform();
void uiRoutine();
void transformationRoutine(GLenum glFaces, GLuint ID);

/*--------------------------------------------------------- Data Variables/Constants --------------------------------------*/

//Dimensions
#define WIDTH 1080
#define HEIGHT 1080

//Window Context
GLFWwindow* window;

//for viewport resizing
int display_w = WIDTH, display_h = HEIGHT;

//ImGui states and control parameters (GUI)
bool show_demo_window = false;
bool wireframe = false;
bool depthTest = true;

// Transform parameters (GUI)
static float fx = 0.0f, fy = 0.0f, fz = -90.0f, scale = 1.0f;

GLuint VBO[1], VAO, EBO;

glm::mat4 MVP;

GLuint volShaderID;
GLuint quadShaderID;

//Texture Objects
GLuint transferFnTexObj;
GLuint quadTexObj;
GLuint volTexObj;

//Isovalue
float iso = 50.0f / 255.0f;

glm::vec3 stepSize = glm::vec3(1.0f/255.0f);

//Camera Position
glm::vec3 camPos = glm::vec3(0.0f, 0.0f, 2.0f);


// Vertices for bounding box
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
    // front
    0, 1, 2,
    2, 3, 0,
    // right
    1, 5, 6,
    6, 2, 1,
    // back
    7, 6, 5,
    5, 4, 7,
    // left
    4, 0, 3,
    3, 7, 4,
    // bottom
    4, 5, 1,
    1, 0, 4,
    // top
    3, 2, 6,
    6, 7, 3
};

float transferFunction[] = {
    1.0f, 1.0f, 1.0f, 0.0f / 6.0f,
    0.0f, 0.0f, 1.0f, 1.0f / 6.0f,
    0.0f, 1.0f, 1.0f, 2.0f / 6.0f,
    0.0f, 1.0f, 0.0f, 3.0f / 6.0f,
    1.0f, 1.0f, 0.0f, 4.0f / 6.0f,
    1.0f, 0.0f, 0.0f, 5.0f / 6.0f,
    0.878431f, 0.0f, 1.0f, 1.0f
};