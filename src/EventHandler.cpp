#include "EventHandler.h"

EventHandler::EventHandler()
{
  isPressed = std::vector<bool> (26, false);
  keyEventHandlers = std::vector<std::function<void()>> (26, []() {});
}

EventHandler::~EventHandler()
{
}

void EventHandler::AddFunction(char key, const std::function<void()> &func)
{
  if (key >= 'a' && key <= 'z') {
    keyEventHandlers[key - 'a'] = func;
  }
}

void EventHandler::ExecuteFunctions()
{
  for (int i = 0; i < 26; i++) if (isPressed[i]) keyEventHandlers[i]();
}

void EventHandler::KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
    int index = key - GLFW_KEY_A;
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
      isPressed[index] = true;
    } else if (action == GLFW_RELEASE) {
      isPressed[index] = false;
    }
  }
}
