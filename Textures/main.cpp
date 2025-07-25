#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "shader_def.cpp"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

char path[200] = "C:\\GitProjects\\LearnOpenGl\\Textures";

void processInput(GLFWwindow* window);
int main() {
	glfwInit();
	//openGL version 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}
	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	unsigned int texture1;
	glGenTextures(1, &texture1);
	
	glBindTexture(GL_TEXTURE_2D,texture1);
	unsigned int texture2;
	glGenTextures(1, &texture2);


	// set the texture wrapping/filtering options (on currently bound texture)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data1 = stbi_load("container.jpg",&width,&height,&nrChannels,0);
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	float vertices[] = {
		// positions	  // colors			// texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,// top right
		0.5f,-0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// bottom right
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,// bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f// top left
	};



	unsigned int indices[] = { 
		0,1,2,
		2,3,0
	};



	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW );
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

	if (data1)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data1);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, texture2);
	
	if (data2)
	{

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	

	stbi_image_free(data2);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	Shader shader = Shader("C:\\GitProjects\\LearnOpenGl\\Textures\\shader.vs","C:\\GitProjects\\LearnOpenGl\\Textures\\shader.fs");

	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "texture1"), 0);
	glUniform1i(glGetUniformLocation(shader.ID, "texture2"), 1);


	
	
	//glm::mat4 trans = glm::mat4(1.0f);
	
	
	
	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		
		glClear(GL_COLOR_BUFFER_BIT);
		
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		
		//check and call events	and swap the buffers	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glBindVertexArray(0);

	glfwTerminate();
	return 0;

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	//cout << "changing "<<endl;
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}