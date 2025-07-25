#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "shader_def.cpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow*, int, int);

void processInput(GLFWwindow*);

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


	//Creating and setting Vertex buffer object
	float vertices[] = {
		-.5f,-.5f,.0f, 1.0f,.0f,.0f,
		.0f,0.5f,.0f, .0f,1.0f,.0f,
		.5f,-.5f,.0f, .0f,.0f,1.0f
	};

	unsigned int indices[]{
		0,1,2,
	};

	//Buffer Objects
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int EBO;
	glGenBuffers(1, &EBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	//Shaders


	Shader shaderProgram = Shader("C:\\GitProjects\\LearnOpenGl\\Shaders\\shader.vs", "C:\\GitProjects\\LearnOpenGl\\Shaders\\shader.fs");

	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(VAO);
		shaderProgram.use();
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "uniColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		//check and call events	and swap the buffers	
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


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


