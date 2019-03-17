#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader.h>
#include <stb_image.h>
#include <filesystem.h>

void on_size_change(GLFWwindow* win, int w, int h)
{
	glViewport(0, 0, w, h);
}

int main()
{
	glm::vec4 vec(1.f, 0.f, 0.f, 1.f);	//[1,0,0]
	glm::mat4 trans = glm::mat4(1.f);
	trans = glm::translate(trans, glm::vec3(1.f, 1.f, 0.f)); //+[1,1,0]
	vec = trans * vec;
	std::cout << vec.x << vec.y << vec.z << std::endl; //[2, 1, 0]

	//system("pause");

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(800, 600, u8"Matrix, transform±ä»»", NULL, NULL);
	if (!win)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(win);
	glfwSetFramebufferSizeCallback(win, on_size_change);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}


	glfwTerminate();
	return 0;
}