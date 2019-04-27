#pragma once
#include <GL\glew.h>
#include <string>
#include <glm\glm.hpp>
class Graphics
{
private:
	float x;
	float y;
	float screenWidth = 800;
	float screenHeight = 600;
	GLuint textShaderProgram;
	std::string textFragmentShaderPath;
	std::string textVertexShaderPath;
	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 model;

public:
	Graphics();
	~Graphics();

	void drawRectangle(float x, float y, float width, float height);
	int installShader(char* vertexShaderPath, char* fragmentShaderPath);
	void drawString(std::string text, float x , float y);
	float getX() { return x; };
	void setX(float x) { this->x = x; };
	float getY() { return y; };
	void setY(float y) { this->y = y; };
	void addX(float x) { this->x += x; };
	void addY(float y) { this->y += y; };
	void reset() {	this->x = 0.0;	this->y = 0.0;};
};

