#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

const char* vertexShader();
const char* fragmentShader();
void compileVertexShader(const char*, unsigned int&);
void compileFragmentShader(const char*, unsigned int&);
void setShaderProgram(unsigned int&, unsigned int&, unsigned int&);
void createVBO(float[], size_t,unsigned int&);
void createVAO(unsigned int&);

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
	
	//Input data
	float vertices1[]{
		.5f,.5f,.0f,
		1.0f,-.5f,.0f,
		.5f,-.5f,.0f,
	};
	float vertices2[]{
		-.5f,-.5f,.0f,
		-.5f,.5f,.0f,
		.0f,-.5f,.0f,
	};

	//Buffer Objects
	unsigned int VBO1{0};
	createVBO(vertices1,sizeof(vertices1), VBO1);
	unsigned int VAO1{0};
	createVAO(VAO1);
	unsigned int VBO2{0};
	createVBO(vertices2, sizeof(vertices2), VBO2);
	unsigned int VAO2{0};
	createVAO(VAO2);


	//Shaders
	const char* vertexShaderSource = vertexShader();
	unsigned int vertexShader;
	compileVertexShader(vertexShaderSource, vertexShader);
	const char* fragmentShaderSource = fragmentShader();
	unsigned int fragmentShader;
	compileFragmentShader(fragmentShaderSource, fragmentShader);
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	setShaderProgram(shaderProgram, vertexShader, fragmentShader);


	//render loop
	while (!glfwWindowShouldClose(window))
	{
		//input
		processInput(window);

		// rendering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES,0,3);
		glBindVertexArray(VAO2);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

const char* vertexShader() {
	const char* shader = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main(){\n"
		"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"};\n";
	return shader;

}
const char* fragmentShader() {
	const char* shader = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main(){\n"
		"FragColor=vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\n";
	return shader;
}
void compileVertexShader(const char* vertexShaderSource, unsigned int& vertexShader) {


	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}
}
void compileFragmentShader(const char* fragmentShaderSource, unsigned int& fragmentShader) {
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	int success;
	char infoLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

}
void setShaderProgram(unsigned int& shaderProgram, unsigned int& vertexShader, unsigned int& fragShader) {
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragShader);
	glLinkProgram(shaderProgram);
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderProgram, 512, NULL, infoLog);
		cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
}
void createVBO(float vertices[], size_t size,unsigned int& VBO) {
	
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

}
void createVAO(unsigned int& VAO) {
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

}