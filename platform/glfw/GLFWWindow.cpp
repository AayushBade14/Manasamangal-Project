#include "./GLFWWindow.h"
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>

GLFWWindow::GLFWWindow(int width, int height, const char* title) : m_iWidth(width),
                                                                   m_iHeight(height)
{
  if(!glfwInit())
  {
    printf("Failed to initalize GLFW!\n");
    exit(1);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_pWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
  if(!m_pWindow)
  {
    printf("Failed to create GLFW window! \n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(m_pWindow);
}

GLFWWindow::~GLFWWindow()
{
  glfwDestroyWindow(m_pWindow);
  glfwTerminate();
}

void GLFWWindow::PollEvents()
{
  glfwPollEvents();
}

bool GLFWWindow::ShouldClose() const
{
  return glfwWindowShouldClose(m_pWindow);
}

int GLFWWindow::GetWidth() const
{
  return m_iWidth;
}

int GLFWWindow::GetHeight() const
{
  return m_iHeight;
}

void GLFWWindow::SwapBuffers()
{
  glfwSwapBuffers(m_pWindow);
}
