#include "Grid.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

void Grid::drawGround(float groundLevel)
{
	GLfloat extent = size; // How far on the Z-Axis and X-Axis the ground extends
	GLfloat stepSize = step;  // The size of the separation between points

	// Set colour to white
	glColor3ub(255, 255, 255);

	
	// Draw our ground grid
	glBegin(GL_LINES);
	for (GLfloat loop = -extent + stepSize; loop < extent; loop += stepSize)
	{
		// Draw lines along Z-Axis
		glColor3f(1.0f,0.0f,0.0f);

		glVertex3f(loop, groundLevel, extent);
		glVertex3f(loop, groundLevel, -extent);

		// Draw lines across X-Axis
		glVertex3f(-extent, groundLevel, loop);
		glVertex3f(extent, groundLevel, loop);
	}
	glEnd();
	glDepthRange(0.1, 100.0);
}

void Grid::drawAxis(GLuint shaderProgram)
{
	
	glLineWidth(2.0f);
	// Draw the world axis
	glUniform3fv(glGetUniformLocation(shaderProgram, "VertexColor"), 1, glm::value_ptr(glm::vec3(0.0, 0.0, 1.0)));
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.f, 0.0f);
	glVertex3f(8.0f, 0.0f, 0.0f);
	glEnd();
	glUniform3fv(glGetUniformLocation(shaderProgram, "VertexColor"), 1, glm::value_ptr(glm::vec3(1.0, 0.0, 0.0)));
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.f, 0.0f);
	glVertex3f(0.0f, 8.0f, 0.0f);
	glEnd();
	glUniform3fv(glGetUniformLocation(shaderProgram, "VertexColor"), 1, glm::value_ptr(glm::vec3(0.0, 1.0, 0.0)));
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.f, 0.0f);
	glVertex3f(0.0f, 0.0f, 8.0f);
	glEnd();

	glLineWidth(1.0f);
	
}

void Grid::paint(GLuint shaderProgram, float groundLevel) {
	size = 128.0f;
	step = 8.0f;
	drawAxis(shaderProgram); 
	// Draw lower ground grid
	glDepthRange(0.2, 100.0);
	glUniform3fv(glGetUniformLocation(shaderProgram, "VertexColor"), 1, glm::value_ptr(glm::vec3(0.6, 0.6, 0.6)));
	drawGround(); // Draw lower ground grid
	glDepthRange(0.3, 100.0);
	step = 4.0f;
	glUniform3fv(glGetUniformLocation(shaderProgram, "VertexColor"), 1, glm::value_ptr(glm::vec3(0.4, 0.4, 0.4)));
	drawGround(); // Draw lower ground grid
}

Grid::Grid(){
	
}

Grid::~Grid(){

}


// Function to draw a grid of lines

