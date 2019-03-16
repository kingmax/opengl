#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "shader.h"

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);
void error_callback(int error, const char* description);

const int WIDTH = 800;
const int HEIGHT = 600;

int main()
{
	std::cout << "hello, glsl" << std::endl;

	//Shader myShader("a.vs", "a.fs");

	//::getchar();

	GLFWwindow* window;

	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(WIDTH, HEIGHT, u8"Hello, Shader", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader myShader("a.vs", "a.fs");

	const float vertices[] = {
		/*0, 1, 1, 
		-1, -1, 1,
		1, 1, 1*/
		-.5, -.5, 1,
		.5,  -.5, 1, 
		0,   .5,  1
	};

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(.2f, .3f, .3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + .5f;
		int vertexColorLocation = glGetUniformLocation(myShader.ID, "outColor");	//in a.fs
		myShader.use();
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}