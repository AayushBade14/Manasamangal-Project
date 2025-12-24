#ifndef MANASA_RENDERER_INTERFACE_H
#define MANASA_RENDERER_INTERFACE_H
//-------------------------------------------------------------------
//  
//  Name: IRenderer.h
//
//  Desc: Renderer interface for the manasa project
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//-------------------------------------------------------------------

class IRenderer
{
public:

  virtual ~IRenderer() = default;
  
  virtual void Init() = 0;
  virtual void BeginFrame() = 0;
  virtual void EndFrame() = 0;
};

#endif
