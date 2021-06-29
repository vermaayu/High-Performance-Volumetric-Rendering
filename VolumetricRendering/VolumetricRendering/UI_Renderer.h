#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define WIDTH 1280
#define HEIGHT 720

class UI
{
private:

	GLFWwindow* window;

	// Our state
	bool show_demo_window = true;
	ImVec4 clear_color = ImVec4(1.0f, 0.57f, 0.64f, 1.00f);

public:
	int uiInit();
	void uiCleanup();
	void renderLoop();
};