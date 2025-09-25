#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

int width = 1920;
int height = 1013;
const char* title = "Manasamangal-Project";
GLFWwindow* window = nullptr;
float lastFrame = 0.0f;
float dt = 0.0f;

class Shader{
  private:
    unsigned int mId;
    std::string LoadFile(const std::string& path){
      std::string code;
      std::ifstream file;
      
      file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
      try{
        file.open(path);
        std::stringstream stream;
        stream << file.rdbuf();
        file.close();
        code = stream.str();
      }
      catch(const std::ifstream::failure& e){
        std::cerr<<"ERROR: Reading shader file! -> "<<path<<" | REASON: "<<e.what()<<std::endl;
      }
      return code;
    }
    unsigned int CompileShader(const std::string& srcCode, bool isVert){
      const char* code = srcCode.c_str();
      int success;
      char infoLog[512];
      unsigned int shader = isVert? glCreateShader(GL_VERTEX_SHADER) : glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(shader,1,&code,NULL);
      glCompileShader(shader);

      glGetShaderiv(shader,GL_COMPILE_STATUS,&success);
      if(!success){
        glGetShaderInfoLog(shader,512,NULL,infoLog);
        std::cerr<<"ERROR: Compiling shader -> "<<infoLog<<std::endl;
      }
      return shader;
    }
    void CreateShaderProgram(unsigned int& vert, unsigned int& frag){
      mId = glCreateProgram();
      glAttachShader(mId, vert);
      glAttachShader(mId, frag);
      glLinkProgram(mId);
      
      int success;
      char infoLog[512];

      glGetProgramiv(mId,GL_LINK_STATUS,&success);
      if(!success){
        glGetProgramInfoLog(mId,512,NULL,infoLog);
        std::cerr<<"ERROR: linking shader program -> "<<infoLog<<std::endl;
      }

      glDeleteShader(vert);
      glDeleteShader(frag);
    }

  public:
    Shader(const std::string& vertPath, const std::string& fragPath){
      std::string vCode = LoadFile(vertPath);
      std::string fCode = LoadFile(fragPath);
      unsigned int vert = CompileShader(vCode, true);
      unsigned int frag = CompileShader(fCode, false);
      CreateShaderProgram(vert,frag);
    }
    ~Shader(){
      glDeleteProgram(mId);
    }

    void Use(){
      glUseProgram(mId);
    }

    template <typename T>
    void SetValue(const std::string& name, const T& val){
      unsigned int loc = glGetUniformLocation(mId, name.c_str());
      
      if constexpr(std::is_same_v<T,int>)
        glUniform1i(loc,val);
      else if constexpr(std::is_same_v<T,bool>)
        glUniform1i(loc,(int)val);
      else if constexpr(std::is_same_v<T,float>)
        glUniform1f(loc,val);
      else if constexpr(std::is_same_v<T,glm::vec2>)
        glUniform2fv(loc,1,glm::value_ptr(val));
      else if constexpr(std::is_same_v<T,glm::vec3>)
        glUniform3fv(loc,1,glm::value_ptr(val));
      else if constexpr(std::is_same_v<T,glm::mat4>)
        glUniformMatrix4fv(loc,1,GL_FALSE,glm::value_ptr(val));
    }
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0,0,width,height);
}

bool IsKeyPressed(GLenum key){
  return glfwGetKey(window,key) == GLFW_PRESS;
}

bool IsKeyReleased(GLenum key){
  return glfwGetKey(window,key) == GLFW_RELEASE;
}

void ProcessInput(){
  if(IsKeyPressed(GLFW_KEY_ESCAPE)){
    glfwSetWindowShouldClose(window,true);
  }
}

void UpdateWindow(){
  glfwGetWindowSize(window, &width, &height);
}

void UpdateTime(){
  float currentFrame = (float)glfwGetTime();
  dt = currentFrame - lastFrame;
  lastFrame = currentFrame;
}

int main(void){
  glfwInit();

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, title, NULL, NULL);

  glfwMakeContextCurrent(window);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  Shader shader("../vert.glsl","../frag.glsl");
  
  float vertices[] = {
    0.0f,0.0f,  0.0f,0.0f,
    1.0f,0.0f,  1.0f,0.0f,
    1.0f,1.0f,  1.0f,1.0f,

    1.0f,1.0f,  1.0f,1.0f,
    0.0f,1.0f,  0.0f,1.0f,
    0.0f,0.0f,  0.0f,0.0f
  };

  unsigned int vbo;
  unsigned int vao;

  glGenVertexArrays(1,&vao);
  glGenBuffers(1,&vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));

  glBindVertexArray(0);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  while(!glfwWindowShouldClose(window)){
    glfwPollEvents();

    ProcessInput();
    UpdateWindow();
    UpdateTime();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model,glm::vec3((float)width,(float)height,1.0f));
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f,(float)width,0.0f,(float)height);
    
    glm::vec2 uRes = {width,height};

    shader.Use();
    shader.SetValue("model",model);
    shader.SetValue("view",view);
    shader.SetValue("projection",projection);
    shader.SetValue("uRes",uRes);
    shader.SetValue("uTime",(float)glfwGetTime());
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
  }
  glDeleteVertexArrays(1,&vao);
  glDeleteBuffers(1,&vbo);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
