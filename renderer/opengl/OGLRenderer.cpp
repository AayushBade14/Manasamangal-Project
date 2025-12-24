#include "./OGLRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstdio>
#include <cstdlib>

void OGLRenderer::Init()
{
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    printf("Failed to initialize GLAD\n");
    exit(1);
  }

  printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
}

void OGLRenderer::BeginFrame()
{
  glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void OGLRenderer::EndFrame()
{
  //the main rendering logic
}
