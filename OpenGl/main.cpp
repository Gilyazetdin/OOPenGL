#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
		-0.5f, 0.25f, 0.0f  
	};
	unsigned int indices[] = 
	{  
		0, 4, 2,   
		1, 5, 3    
	};
	
	// Проекционная матрица : 45&deg; поле обзора, 4:3 соотношение сторон, диапазон : 0.1 юнит <-> 100 юнитов
	glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);

	// Или, для ортокамеры
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Камера находится в мировых координатах (4,3,3)
		glm::vec3(0, 0, 0), // И направлена в начало координат
		glm::vec3(0, 1, 0)  // "Голова" находится сверху
	);
	// Матрица модели : единичная матрица (Модель находится в начале координат)
	glm::mat4 Model = glm::mat4(1.0f);  // Индивидуально для каждой модели

	// Итоговая матрица ModelViewProjection, которая является результатом перемножения наших трех матриц
	glm::mat4 MVP = Projection * View * Model; // Помните, что умножение матрицы производиться в обратном порядке

	run.setInput(inputSwitch);
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	GLuint VBO;
	glGenBuffers(1, &VBO);
	GLuint IBO;
	glGenBuffers(1, &IBO);
	while (!window.isClosing())
	{
		run.callInput();

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);	
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Получить хэндл переменной в шейдере
		// Только один раз во время инициализации.
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		run.useProgram();

		GLuint matrix = glGetUniformLocation(shader.getId(), "MVP");
		
		MVP = glm::rotate(MVP, cos((GLfloat)glfwGetTime())/2.0f, glm::vec3(0.0f, 0.0f, 1.0f));

		// Передать наши трансформации в текущий шейдер
		// Это делается в основном цикле, поскольку каждая модель будет иметь другую MVP-матрицу (как минимум часть M)
		glUniformMatrix4fv(matrix, 1, GL_FALSE, glm::value_ptr(MVP));


		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window.glfw_window);
		glfwPollEvents();
	}

	return 0;
}

