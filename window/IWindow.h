#ifndef MANASA_WINDOW_INTERFACE_H
#define MANASA_WINDOW_INTERFACE_H
//--------------------------------------------------------------------
//  
//  Name: IWindow.h
//
//  Desc: Interface for the windowing tasks
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//--------------------------------------------------------------------

class IWindow
{
public:
  
  virtual ~IWindow() = default;

  virtual void PollEvents() = 0;
  virtual bool ShouldClose() const = 0;

  virtual int GetWidth() const = 0;
  virtual int GetHeight() const = 0;

  virtual void SwapBuffers() = 0;
};

#endif
