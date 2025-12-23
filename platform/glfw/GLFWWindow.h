#ifndef MANASA_GLFW_WINDOW_H
#define MANASA_GLFW_WINDOW_H
//-------------------------------------------------------------------
//  
//  Name: GLFWWindow.h
//
//  Desc: GLFW implementation for the window interface
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//--------------------------------------------------------------------

#include "../../window/IWindow.h"

struct GLFWwindow;

class GLFWWindow : public IWindow
{
public:

  GLFWWindow(int width, int height, const char* title);
  ~GLFWWindow();

  void PollEvents() override;
  bool ShouldClose() const override;

  int GetWidth() const override;
  int GetHeight() const override;

  void SwapBuffers() override;

private:

  GLFWwindow* m_pWindow;
  int m_iWidth;
  int m_iHeight;
};

#endif
