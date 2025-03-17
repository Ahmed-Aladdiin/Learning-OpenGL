#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include <functional>

class EventHandler
{
private:
  std::vector<bool> isPressed;
  std::vector<std::function<void()>> keyEventHandlers;

public:
  EventHandler();
  ~EventHandler();

  // Method to add a function to the vector
  void AddFunction(char key, const std::function<void()>& func);

  // Method to execute all functions in the vector
  void ExecuteFunctions();

  void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};
