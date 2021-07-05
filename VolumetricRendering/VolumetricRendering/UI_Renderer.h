#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include<iostream>
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1280
#define HEIGHT 720

class UI
{
private:

	GLFWwindow* window;
    unsigned int vertexShader, fragmentShader, shaderProgram;
    unsigned int VBO, VAO, EBO;


	//ImGui states
	bool show_demo_window = false;
	ImVec4 clear_color = ImVec4(1.0f, 0.57f, 0.64f, 1.00f);

    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

public:
	int uiInit();
	void uiCleanup();
	void renderLoop();
};