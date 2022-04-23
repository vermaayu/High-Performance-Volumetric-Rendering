#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <iostream>
#include <fstream> 
#include <vector>
#include "Shader.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1280
#define HEIGHT 720

class UI
{
private:

	GLFWwindow* window;
    GLuint vertexShader, fragmentShader, shaderProgram;
	GLuint VBO, VAO, EBO;


	//ImGui states
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(1.0f, 0.57f, 0.64f, 1.00f);
	
	//Shader declaration
	Shader shaderProgram("shaders/shader.vert", "shaders/shader.frag");

	/*std::ifstream vertexShaderSource(("shaders/shader.vert").c_str());
	std::ifstream fragmentShaderSource(("shaders/shader.frag").c_str());*/
	//const char* fragmentShaderSource = ;

public:
	int uiInit();
	void uiCleanup();
	void renderLoop();

};