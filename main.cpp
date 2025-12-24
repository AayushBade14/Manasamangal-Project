#include "./core/Application.h"
#include "./platform/glfw/GLFWWindow.h"
#include "./renderer/opengl/OGLRenderer.h"

int main(void)
{
  GLFWWindow window(800, 600, "Engine Window");
  OGLRenderer renderer;
  renderer.Init();

  Application app(&window, &renderer);
  app.Run();

  return 0;
}
