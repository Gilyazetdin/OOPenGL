#include "Run.h"

void stdCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

Run::Run(int contextVersionMajor, int contextVersionMinor)
{
	assert(contextVersionMajor >= 0 || contextVersionMinor >= 0);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}
Run::~Run()
{
	delete[] shaderPointer->vertexShaderSource;
	delete[] shaderPointer->fragmentShaderSource;
	glfwTerminate();
}
void Run::setWindow(Window& window, GLFWframebuffersizefun callback)
{
	windowPointer = &window;
	glfwMakeContextCurrent(window.glfw_window);
	glfwSetFramebufferSizeCallback(window.glfw_window, callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		throw new std::runtime_error("Error with init GLAD.");
	}
}
void Run::setShader(Shader& shader)
{
	shaderPointer = &shader;
}
void Run::setInput(std::function<void(Window&)> function)
{
	input_function = function;
}
void Run::callInput()
{
	input_function(*windowPointer);
}
void Run::useProgram()
{
	glUseProgram(shaderPointer->getId());
}



