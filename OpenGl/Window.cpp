#include "Window.h"



Window::Window(int w, int h, const std::string& name)
{
	setWidth(w);
	setHeight(h);

	glfw_window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
	if (glfw_window == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Error with creating window");
	}
	glfwMakeContextCurrent(glfw_window);
}
Window::~Window()
{
}

bool Window::isPressed(int key, int what)
{
	return glfwGetKey(glfw_window, key) == what;
}

void Window::shouldClose()
{
	glfwSetWindowShouldClose(glfw_window, true);
}
bool Window::isClosing()
{
	return glfwWindowShouldClose(glfw_window);
}

void Window::setWidth(int w)
{
	assert(w > 0);
	width = w;
}
int Window::getWidth()
{
	return width;
}

void Window::setHeight(int h)
{
	assert(h > 0);
	height = h;
}
int Window::getHeight()
{
	return height;
}