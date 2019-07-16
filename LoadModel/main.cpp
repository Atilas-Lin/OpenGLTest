#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
using namespace std;
#include "Camera.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma region Screen functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
#pragma endregion

#pragma region Initial Settings
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0, 0, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
#pragma endregion

#pragma region Model Data
float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
// world space positions of our cubes
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion 

// string.c_str() 可將一個字串轉乘寫死的字符串(string -> const char*)
unsigned int LoadImageToGPU(const char* fileName, GLint internalFormat, GLenum format, int textureSlot)
{
	unsigned int TexBuffer;
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glGenTextures(1, &TexBuffer);

	glBindTexture(GL_TEXTURE_2D, TexBuffer);

	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
	unsigned char *data = stbi_load(fileName, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	return TexBuffer;
}

int main() {

	#pragma region Open a Window
	glfwInit();
	// OpenGL版本
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
	glfwSetScrollCallback(window, scroll_callback);

	//Init GLEW
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		cout << "glew init failed." << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT); 
#pragma endregion

	glEnable(GL_DEPTH_TEST);

	#pragma region Init Shader Program
		Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion

	#pragma region Init and Load Models to VAO, VBO
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
#pragma endregion

	#pragma region Init and Load Textures
	// load and create a texture 
	unsigned int texture1, texture2;
	texture1 = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
	#pragma endregion

	// render loop
	while (!glfwWindowShouldClose(window))
	{
		#pragma region MVP matrices
		glm::mat4 modelMat;
		glm::mat4 viewMat;
		glm::mat4 projectMat;
		viewMat = camera.GetViewMatrix();
		projectMat = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / SCR_HEIGHT, 0.1f, 100.0f);
		#pragma endregion

		#pragma region pre-frame time of Camera
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		#pragma endregion

		// Process input
		processInput(window); //套用(前一次迴圈的)用戶輸入

		// Clear Screen
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Set Material -> Shader Program
		myShader->use();
		// Set Material -> Textures
		//glActiveTexture(GL_TEXTURE0);
		//glBindTexture(GL_TEXTURE_2D, texture1);
		// Set Material -> Uniforms
		//myShader->setInt("ourTexture", 0);
		myShader->setMat4("viewMat", viewMat);
		myShader->setMat4("projectMat", projectMat);
		myShader->setVec3("objColor", 1.0f, 0.5f, 0.31f);
		myShader->setVec3("ambientColor", 1.0f, 1.0f, 1.0f);
		myShader->setVec3("lightPos", 10.0f, 10.0f, 5.0f);
		myShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		// Drawcall
		for (unsigned int i = 0; i < 10; i++)
		{
			// Set Model matrix
			modelMat = glm::mat4(1.0f);
			modelMat = glm::translate(modelMat, cubePositions[i]);

			// Set View and Projection Matrices here if you want
			//

			myShader->setMat4("modelMat", modelMat);
			// Set Model
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Clean up, prepare for next render loop
		glfwPollEvents(); //獲取用戶輸入(下一次迴圈時才被processInput採用)
		glfwSwapBuffers(window);
	}

	// Exit program
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Whenever the mouse moves, this callback is call
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	//防止第一筆資料暴衝
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xPos - lastX;
	deltaY = yPos - lastY;
	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(deltaX, deltaY);
}

// Whenever the mouse scroll wheel scrolls, this callback is call
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}