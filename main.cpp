#include "./core/Application.h"
#include "./platform/glfw/GLFWWindow.h"

int main(void)
{
  GLFWWindow window(800, 600, "Engine Window");
  Application app(&window);
  app.Run();

  return 0;
}
