#include "./Application.h"
#include "../window/IWindow.h"
#include "../renderer/IRenderer.h"

Application::Application(IWindow* window, IRenderer* renderer) : m_pWindow(window),
                                                                 m_pRenderer(renderer)
{}

void Application::Run()
{
  while(!m_pWindow->ShouldClose())
  {
    m_pRenderer->BeginFrame();

    m_pWindow->PollEvents();
    m_pWindow->SwapBuffers();
  }
}
