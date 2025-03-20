#include "Camera.h"
#define GLM_ENABLE_EXPERIMENTAL 

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include <iostream>

Camera::Camera(glm::vec3 _eye, float _speed, float _sensitivity, float _width, float _height)
: eye(_eye), speed(_speed), sensitivity(_sensitivity), width(_width), height(_height), firstClick(true)
{
  viewDirection = glm::vec3(0, 0, -1);
  up = glm::vec3(0, 1, 0);
}

Camera::~Camera()
{
}

glm::mat4 Camera::GetLookAtMat()
{
  return glm::lookAt(eye, eye + viewDirection, up);
}

void Camera::Inputs(GLFWwindow* window)
{
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		eye += speed * viewDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		eye += speed * -glm::normalize(glm::cross(viewDirection, up));
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		eye += speed * -viewDirection;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		eye += speed * glm::normalize(glm::cross(viewDirection, up));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		eye += speed * up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		eye += speed * -up;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 0.1f;
	}


	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hides mouse cursor
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
      mousePrevPos = glm::vec2(width/2.0, height/2.0);
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;
		// Fetches the coordinates of the cursor
		glfwGetCursorPos(window, &mouseX, &mouseY);
    std::cout << "mouse: " << mouseX << ' ' << mouseY << std::endl;

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees 
    glm::vec2 mouseCurrPos = glm::vec2(mouseX, mouseY);
    glm::vec2 mouseMovement = mousePrevPos - mouseCurrPos;
    mousePrevPos = mouseCurrPos;

		float rotX = 360.0f * mouseMovement.y / height;
		float rotY = 360.0f * mouseMovement.x / width;

		// Calculates upcoming vertical change in the viewDirection
		glm::vec3 newviewDirection = glm::rotate(viewDirection, glm::radians(rotX), glm::normalize(glm::cross(viewDirection, up)));

		// Decides whether or not the next vertical viewDirection is legal or not
    float angle = glm::angle(newviewDirection, up) - glm::radians(90.0f);
    if (angle < 0) angle *= -1;

    std::cout << "angle: " << angle << "relative to: " << glm::radians(70.0f) << std::endl;
		if ( angle <= glm::radians(70.0f))
		{
			viewDirection = newviewDirection;
		}

		// Rotates the viewDirection left and right
		viewDirection = glm::rotate(viewDirection, glm::radians(rotY), up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
		// glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		// Makes sure the next time the camera looks around it doesn't jump
		firstClick = true;
	}
}