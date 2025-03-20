#include "EventHandler.h"

EventHandler::EventHandler()
{
  isPressed = std::vector<bool> (350, false);
  keyEventHandlers = std::vector<std::function<void()>> (350, []() {});
}

EventHandler::~EventHandler()
{
}

void EventHandler::AddFunction(char key, const std::function<void()> &func)
{
  if (key >= 0 && key < 350) {
    keyEventHandlers[key] = func;
  }
}

void EventHandler::ExecuteFunctions()
{
  for (int i = 0; i < 350; i++) if (isPressed[i]) keyEventHandlers[i]();
}

void EventHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (action == GLFW_PRESS || action == GLFW_REPEAT) {
    isPressed[key] = true;
  } else if (action == GLFW_RELEASE) {
    isPressed[key] = false;
  }
}
