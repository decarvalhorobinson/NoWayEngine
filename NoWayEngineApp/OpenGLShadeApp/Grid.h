#pragma once
#include "Grid.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Grid
{
public:
	void drawGround(float groundLevel = 0.0f);
	void drawAxis(GLuint shaderProgram);
	void paint(GLuint shaderProgram, float groundLevel = 0.0f);
	Grid();
	~Grid();
	float size;
	float step;
private:

};

