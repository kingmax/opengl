#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <Windows.h>

const int WIDTH = 800;
const int HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow*, int, int);
void processInput(GLFWwindow*);

void HideConsoleWindow()
{
	//Windows.h
	::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

//const char* vs_shader =
//"#version 330 core"
//"layout (location = 0) in vec3 aPos;"
//"void main()"
//"{"
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);"
//"}";

//const char* vs_shader = 
//"#version 330 core \n\
//layout (location = 0) in vec3 pos; \n\
//void main() \n\
//{ \n\
//	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0); \n\
//} \n\
//";

const char* vs_shader = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)";

const char* fs_shader = R"(#version 330 core
out vec4 FragColor;
void main()
{
	//FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	FragColor = vec4(0.1f, 0.6f, 0.1f, 1.0f);
}
)";

//vertex data
const float vertices[] = {
	-0.5f, -0.5f, 0.0f,	//buttom left
	0.5f,  -0.5f, 0.0f, //buttom right
	0.0f,  0.5f,  0.0f  //top
};

const float vertices2[] = {
	0.5f,  0.5f,  0.0f, //top right
	0.5f,  -0.5f, 0.0f,	//buttom right
	-0.5f, -0.5f, 0.0f, //buttom left
	-0.5f,  0.5f,  0.0f  //top left
};

const unsigned int indices[] = {
	0, 1, 3, //first triangle
	1, 2, 3  //second triangle
};

int main()
{
	/*const char* txt = "hello";
	std::cout << txt << std::endl;
	getchar();*/

	/*std::cout << vs_shader << std::endl;
	std::cout << fs_shader << std::endl;
	getchar();*/

	//HideConsoleWindow();

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, /*TEXT("Hello, Triangle")*/"Hello, Triangle", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//build and compile shader program
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vs_shader, NULL);
	glCompileShader(vertexShader);
	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fs_shader, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//link shader
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//set up vertex data (and buffer(s)) and configure vertex attributes
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO); //init VAO
	glGenBuffers(1, &VBO);		//init VBO

	//Element Buffer Object (Index Buffer Object)
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);*/

	//bind the Vretex Array Object first, then bind and set vertex buffer(s), and then configure vertex attribute(s)
	glBindVertexArray(VAO);

	//send vertex data to gpu
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);	//unbind VAO

	//wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Render Loop
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		//rendering
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//draw out first triangle
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		//glBindVertexArray(0); //no need to unbind it every time

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	return 0;
}



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//point
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		std::cout << "F3 pressed, switch to Point mode" << std::endl;
	}
	//wireframe
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		std::cout << "F3 pressed, switch to Wireframe mode" << std::endl;
	}
	//face
	if (glfwGetKey(window, GLFW_KEY_F4) == GLFW_PRESS)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		std::cout << "F4 pressed, switch to Face mode" << std::endl;
	}
}
