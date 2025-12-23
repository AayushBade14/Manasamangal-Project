#include "./Application.h"
#include "../window/IWindow.h"

Application::Application(IWindow* window) : m_pWindow(window)
{}

void Application::Run()
{
  while(!m_pWindow->ShouldClose())
  {
    m_pWindow->PollEvents();
    m_pWindow->SwapBuffers();
  }
}
