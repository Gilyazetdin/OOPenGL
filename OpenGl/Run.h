#pragma once
// init -> window -> shader -> VBO -> mainloop

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <cassert>
#include <stdexcept>
#include <functional>

#include "Window.h"
#include "Shader.h"

void stdCallback(GLFWwindow* window, int width, int height);



class Run
{
public:
	Run(int contextVersionMajor, int contextVersionMinor);
	~Run();

	void setWindow(Window& window, GLFWframebuffersizefun callback = stdCallback);
	void setShader(Shader& shader);
	void setInput(std::function<void(Window&)> function);
	void callInput();
	void useProgram();
private:
	std::function<void(Window&)> input_function;
	Window* windowPointer;
	Shader* shaderPointer;
};


