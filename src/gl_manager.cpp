#include "gl_manager.hpp"

// コールバック関数
void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

// void MouseCallback(GLFWwindow *window, double xpos, double ypos)
// {
//     if(first_mouse)
//     {
//         last_x = xpos;
//         first_mouse = false;
//     }
// 
//     float xoffset = xpos - last_x;
//     last_x = xpos;
// 
//     float sensitivity = 0.1f;
//     xoffset *= sensitivity;
// 
//     theta += xoffset;
// 
//     camera->Update(vec3(5.0f*cos(theta), 0.5f, 5.0f*sin(theta)), vec3(0.0, 1.0, 0.0), glm::vec3(0.0f, 0.0f, 0.0f));
// }

GLManager::GLManager()
{
    /**** GLFW初期化 ****/

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->openglVersionMejor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->openglVersionMinor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    std::atexit(glfwTerminate);

    this->window = glfwCreateWindow(this->windowWidth, this->windowHeight, title.data(), NULL, NULL);

    if(window == NULL)
    {
        std::cerr << "Falied to create GLFW window" << std::endl;
        exit(1);
    }

    glfwMakeContextCurrent(this->window);

    glfwSetKeyCallback(this->window, KeyCallback);
    // glfwSetCursorPosCallback(this->window, CursorPosCallback);

    /**** GLEW初期化 ****/

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        exit(1);
    }

    /**** 描画設定 ****/

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(this->backgroundColor.r, this->backgroundColor.g, this->backgroundColor.b, this->backgroundColor.a);

    // Retina Displayの場合は2倍にする必要がある
    glViewport(0, 0, 2*this->windowWidth, 2*this->windowHeight);
}

int GLManager::getWindowWidth() const { return this->windowWidth; }
int GLManager::getWindowHeight() const { return this->windowHeight; }