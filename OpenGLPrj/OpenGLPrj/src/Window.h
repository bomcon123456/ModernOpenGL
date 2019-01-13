#ifndef WINDOW_H
#define WINDOW_H
#include "Core.h"

class Window
{
  public:
	Window();
	Window(const int &width, const int &height, const char* name = "OpenGL");
	~Window();

	bool Initialize();

	int GetBufferWidth() { return m_bufferWidth; }
	int GetBufferHeight() { return m_bufferHeight; }

	bool GetShouldClose() { return glfwWindowShouldClose(m_mainWindow); };

	void SwapBuffers() { glfwSwapBuffers(m_mainWindow); };

  private:
	GLFWwindow *m_mainWindow;

	const char* m_windowName;
	int m_width, m_height;
	int m_bufferWidth, m_bufferHeight;
};
#endif
