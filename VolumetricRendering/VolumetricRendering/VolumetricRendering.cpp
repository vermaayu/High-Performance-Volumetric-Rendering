/// VolumetricRendering.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "UI_Renderer.h"
#include <iostream>

int main(int, char**)
{
    UI ui;
    int error = ui.uiInit();
    if (error != 0)
        std::cout << "Error Code: " << error << std::endl;

    ui.renderLoop();
    ui.uiCleanup();

    return 0;
}
