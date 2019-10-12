#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <string>

#include "Window.h"
#include "Shader.h"
#include "Run.h"
#include "Buffer.h"
#include "GlArray.h"

void inputSwitch(Window& window)
{
	if (window.isPressed(GLFW_KEY_ESCAPE))
	{
		window.shouldClose();
	}
}



int main()
{
	
	std::ios::sync_with_stdio(false);

	Run run(4, 4);

	Window window(800, 500, "test");
	run.setWindow(window);
	
	Shader shader("vertexShader.glsl", "fragmentShader.glsl");
	run.setShader(shader);
	
	
	float vertices[] = 
	{
		 0.0f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,
		 0.5f, 0.25f, 0.0f,   0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,
		 0.0f, -0.75f, 0.0f,  1.0f, 0.0f, 1.0f,
		 -0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f,
		 -0.5f, 0.25f, 0.0f,  0.0f, 1.0f, 1.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 4, 2,   // first triangle
		1, 5, 3    // second triangle
	};
	
	run.setInput(inputSwitch);
	
	GlArray* VAO = new GlArray();
	Buffer* VBO = new Buffer();
	Buffer* IBO = new Buffer();

	while (!window.isClosing())
	{
		run.callInput();

		VAO->bindVertices(*VBO, vertices, GL_STATIC_DRAW);
		VAO->bindIndices(*IBO, indices, GL_STATIC_DRAW);
		
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		run.useProgram();
	

		glBindVertexArray(VAO->getArrayObject()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window.glfw_window);
		glfwPollEvents();
	}
	delete VAO, VBO, IBO;
	return 0;
}

