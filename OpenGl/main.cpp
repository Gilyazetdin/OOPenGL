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
		 0.0f,  0.5f, 0.0f, 
		 0.5f, 0.25f, 0.0f,  
		 0.5f, -0.5f, 0.0f,   
		 0.0f, -0.75f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
		 -0.5f, 0.25f, 0.0f,
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 4, 2,   // first triangle
		1, 5, 3    // second triangle
	};
	
	run.setInput(inputSwitch);

	while (!window.isClosing())
	{
		run.callInput();

		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		GLuint VBO;
		glGenBuffers(1, &VBO);
		GLuint EBO;
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
		// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
		glBindVertexArray(0);
		
		
		

		glClearColor(0.1f, 0.3f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		run.useProgram();
		
		GLfloat time= glfwGetTime();
		GLfloat red = (sin(time) / 2) + 0.5f;
		GLfloat green = cos(time) / 2 + sin(time) / 2;
		GLfloat blue = cos(time) - sin(time) / 2 + 0.5f;
		
		GLint vertexColorLocation = glGetUniformLocation(shader.getId(), "ourColor");
		glUniform4f(vertexColorLocation, red, green, blue, 1.0f);

		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window.glfw_window);
		glfwPollEvents();
	}

	return 0;
}

