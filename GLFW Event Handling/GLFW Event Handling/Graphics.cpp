#include "Graphics.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Graphics::Graphics()
{
	//projection = glm::perspective(45.0f, (float)screenWidth / (float)screenHeight, 0.01f, 1000.0f);
	projection = glm::ortho( 0.0f, screenWidth, screenHeight, 0.0f, 0.01f, 1000.0f);
	view = glm::lookAt(glm::vec3(0.0, 0.0, 6), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
}


Graphics::~Graphics()
{
}


void Graphics::drawRectangle(float x, float y, float width, float height)
{
	//fix the position to the relative position
	x += this->x;
	y += this->y;
	float size = 900.5f;
	float vertices[] = {
		(float)x, (float)y, 0.f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f,

		(float)x + (float)width, (float)y, 0.f,
		1.0f, 1.0f, 0.0f,
		0.0f, 0.0f,

		(float)x + (float)width, (float)y + (float)height, 0.f,
		0.0f, 1.0f, 1.0f,
		0.0f, 0.0f,

		(float)x, (float)y + (float)height, 0.f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f

	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);//create the buffer id
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);// bind the buffer with the current type os buffer to use 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);// store the data

	glEnableVertexAttribArray(0);// mark the buffer to its attrib 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);// mark the buffer to its attrib 1 location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 3));

	glEnableVertexAttribArray(2);// mark the buffer to its attrib 2 location
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(3));

	GLushort indices[] = { 2,1,0,0,3,2 };// start on zero
	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	int program = installShader("vertexShader.glsl", "fragmentShader.glsl");
	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "projection");
	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (char*)(0));
	glUseProgram(0);


}

int Graphics::installShader(char* vertexShaderPath,char* fragmentShaderPath) {

	char* path1 = fragmentShaderPath;
	std::ifstream in1(path1);
	std::string src1 = "";
	std::string line1 = "";
	while (std::getline(in1, line1))
		src1 += line1 + "\n";



	char* path2 = vertexShaderPath;
	std::ifstream in2(path2);
	std::string src2 = "";
	std::string line2 = "";
	while (std::getline(in2, line2))
		src2 += line2 + "\n";


	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);



	const char* source1 = src1.c_str();
	glShaderSource(fragmentShaderID, 1, &source1, NULL);
	glCompileShader(fragmentShaderID);

	const char* source2 = src2.c_str();
	glShaderSource(vertexShaderID, 1, &source2, NULL);
	glCompileShader(vertexShaderID);




	GLuint programID = glCreateProgram();


	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	glLinkProgram(programID);
	GLint linked;
	glGetProgramiv(programID, GL_LINK_STATUS, &linked);
	//Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(programID, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(programID, maxLength, &maxLength, &infoLog[0]);

		for (size_t i = 0; i < maxLength; i++)
		{
			std::cout << infoLog[i] << "";
		}
		//We don't need the program anymore.
		glDeleteProgram(programID);
		//Don't leak shaders either.
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);

		//Use the infoLog as you see fit.

		//In this simple program, we'll just leave
		return 0;
	}

	glUseProgram(programID);
	return programID;


}

void Graphics::drawString(std::string text, float x, float y)
{
	//fix the position to the relative position
	x += this->x;
	y += this->y;
}
