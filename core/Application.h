#ifndef MANASA_APPLICATION_H
#define MANASA_APPLICATION_H
//-------------------------------------------------------------------
//  
//  Name: Application.h
//
//  Desc: Application class for the manasa project
//
//  Author: Aayush Bade 2025 (aayushbade14.github.io/Portfolio)
//
//-------------------------------------------------------------------

class IWindow;

class Application
{
public:

  Application(IWindow* window);
  
  void Run();

private:

  IWindow* m_pWindow;
};

#endif
