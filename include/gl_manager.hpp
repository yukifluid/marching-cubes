#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>
#include <string>

class GLManager
{
public:
    GLManager();

public:
    GLFWwindow* window;

    int getWindowWidth() const;
    int getWindowHeight() const;

private:
    // OpenGL設定
    const int openglVersionMejor = 3;
    const int openglVersionMinor = 3;

    // ウィンドウ設定
    const int windowWidth   = 600;
    const int windowHeight  = 600;
    const std::string title = "Fluids Visualization";

    // 描画設定
    const glm::vec4 backgroundColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
};