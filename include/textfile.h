#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

std::string readShaderSource(const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open shader file: " << filepath << std::endl;
    exit(EXIT_FAILURE);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

GLuint compileShader(GLenum type, const std::string &source) {
  GLuint shader = glCreateShader(type);
  const char *src = source.c_str();
  glShaderSource(shader, 1, &src, nullptr);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    std::cerr << "Shader compilation error: " << infoLog << std::endl;
    exit(EXIT_FAILURE);
  }
  return shader;
}

GLuint createShaderProgram(const std::string &vertexPath,
                           const std::string &fragmentPath) {
  std::string vertexCode = readShaderSource(vertexPath);
  std::string fragmentCode = readShaderSource(fragmentPath);

  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexCode);
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentCode);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetProgramInfoLog(program, 512, nullptr, infoLog);
    std::cerr << "Shader program linking error: " << infoLog << std::endl;
    exit(EXIT_FAILURE);
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return program;
}