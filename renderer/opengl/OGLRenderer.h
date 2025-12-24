#ifndef MANASA_OGL_RENDERER_H
#define MANASA_OGL_RENDERER_H
//------------------------------------------------------------------
//  
//  Name: OGLRenderer.h
//
//  Desc: OpenGL implementation for the Renderer Interface
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//------------------------------------------------------------------

#include "../IRenderer.h"

class OGLRenderer : public IRenderer
{
public:

  void Init() override;
  void BeginFrame() override;
  void EndFrame() override;

};

#endif
