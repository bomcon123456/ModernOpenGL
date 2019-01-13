#ifndef WINDOW_H
#define WINDOW_H
#include "Core.h"

class Window
{
  public:
	Window();
	Window(const int &width, const int &height, const char *name = "OpenGL");
	~Window();

	bool Initialize();

	int GetBufferWidth() { return m_bufferWidth; }
	int GetBufferHeight() { return m_bufferHeight; }

	bool GetShouldClose() { return glfwWindowShouldClose(m_mainWindow); };

	bool *GetKey() { return m_keys; }
	float GetXChange();
	float GetYChange();

	void SwapBuffers() { glfwSwapBuffers(m_mainWindow); };

  private:
	GLFWwindow *m_mainWindow;

	const char *m_windowName;
	int m_width, m_height;
	int m_bufferWidth, m_bufferHeight;

	bool m_keys[1024];
	float m_lastX;
	float m_lastY;
	float m_xChange;
	float m_yChange;
	bool m_mousedFirstMoved = true;

	void CreateCallbacks();
	static void HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);
	static void HandleMouse(GLFWwindow *window, double xPos, double yPos);
};
#endif
