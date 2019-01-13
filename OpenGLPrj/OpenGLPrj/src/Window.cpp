#include "Window.h"

Window::Window() : m_width(800), m_height(600)
{
    for (int i = 0; i < 1024; i++)
    {
        m_keys[i] = 0;
    }
}
Window::Window(const int &w, const int &h, const char *name) : m_windowName(name), m_width(w), m_height(h)
{
    for (int i = 0; i < 1024; i++)
    {
        m_keys[i] = 0;
    }
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

    CreateCallbacks();
    glfwSetInputMode(m_mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

    glfwSetWindowUserPointer(m_mainWindow, this);

    return 1;
}

float Window::GetXChange()
{
	float res = m_xChange;
	m_xChange = 0.f;
	return res;
}

float Window::GetYChange()
{
	float res = m_yChange;
	m_yChange = 0.f;
	return res;
}

void Window::CreateCallbacks()
{
    glfwSetKeyCallback(m_mainWindow, HandleKeys);
    glfwSetCursorPosCallback(m_mainWindow, HandleMouse);
}

void Window::HandleKeys(GLFWwindow *window, int key, int code, int action, int mode)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);   
    }
    if(key >= 0 && key < 1024)
    {
        if(action == GLFW_PRESS)
        {
            theWindow->m_keys[key] = true;       
        }
        else if(action == GLFW_RELEASE)
        {
            theWindow->m_keys[key] = false;
        }
    }
}

void Window::HandleMouse(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if(theWindow->m_mousedFirstMoved)
    {
        theWindow->m_lastX = xPos;
        theWindow->m_lastY = yPos;
        theWindow->m_mousedFirstMoved = false;
    }

    theWindow->m_xChange = xPos - theWindow->m_lastX;
    theWindow->m_yChange = theWindow->m_lastY - yPos;

    theWindow->m_lastY = yPos;
    theWindow->m_lastX = xPos;

}
