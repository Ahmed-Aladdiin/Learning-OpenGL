#pragma once

#include <glm.hpp>
#include <GLFW/glfw3.h>

class Camera
{
private:
  glm::vec3 eye;
  glm::vec3 viewDirection;
  glm::vec3 up;

  float speed = 0.1f;
  float sensitivity = 100.0f;

  float width;
  float height;

  bool firstClick;
  glm::vec2 mousePrevPos;
public:
  Camera(glm::vec3 _eye, float _speed, float _sensitivity, float _width, float _height);
  ~Camera();

  glm::mat4 GetLookAtMat();
  void Inputs(GLFWwindow* window);
};

