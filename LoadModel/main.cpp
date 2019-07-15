#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

// Screen functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

	glfwInit();

	// OpenGL����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// open GLFW Window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Load Model Test", NULL, NULL);

	if (window == NULL)
	{
		cout << "open window failed." << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetScrollCallback(window, scroll_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "glew init failed." << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); 
    //�c����/�I��
	//glEnable(GL_CULL_FACE); 
	//glCullFace(GL_BACK);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//glEnable(GL_DEPTH_TEST);

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window); //�M��(�e�@���j�骺)�Τ��J

		// render commands...
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		

		// check and call events and swap the buffers
		glfwPollEvents(); //����Τ��J(�U�@���j��ɤ~�QprocessInput�ĥ�)
		glfwSwapBuffers(window);
	}

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}