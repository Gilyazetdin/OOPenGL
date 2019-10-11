#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <stdexcept>
#include <cassert>

class Window
{
public:
	GLFWwindow* glfw_window;

	Window(
		int w,
		int h,
		const std::string& name
	);
	~Window();

	bool isPressed(int key, int what = GLFW_PRESS);

	void shouldClose();
	bool isClosing();

	void setWidth(int w);
	int getWidth();

	void setHeight(int h);
	int getHeight();

private:
	int width;
	int height;
};

