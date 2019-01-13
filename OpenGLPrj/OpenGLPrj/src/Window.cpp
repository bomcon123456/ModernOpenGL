#include "Window.h"

Window::Window() : m_width(800), m_height(600)
{
}
Window::Window(const int &w, const int &h, const char* name) : m_windowName(name), m_width(w), m_height(h)
{
}

Window::~Window()
{
    glfwDestroyWindow(m_mainWindow);
    glfwTerminate();
}

bool Window::Initialize()
{
    if (glfwInit() != GLFW_TRUE)
    {
        std::cout << "[INITIALIZE] Failed to init GLFW" << std::endl;
        return 0;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    m_mainWindow = glfwCreateWindow(m_width, m_height, m_windowName, NULL, NULL);
    if (!m_mainWindow)
    {
        std::cout << "[INITIALIZE] Failed to create window" << std::endl;
        glfwTerminate();
        return 0;
    }

    glfwMakeContextCurrent(m_mainWindow);

    glfwGetFramebufferSize(m_mainWindow, &m_bufferWidth, &m_bufferHeight);

    glewExperimental = true;

    if (glewInit() != GLEW_OK)
    {
        std::cout << "[INITIALIZE] Failed to init GLEW" << std::endl;
        glfwDestroyWindow(m_mainWindow);
        glfwTerminate();
        return 0;
    }

	GLCall(glEnable(GL_DEPTH_TEST));

	GLCall(glViewport(0, 0, m_bufferWidth, m_bufferHeight));
	return 1;
}
