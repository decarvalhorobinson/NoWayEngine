#pragma once
#include "glm\glm.hpp"
#include <vector>
#include <GL/glew.h>

struct Vertex
{
	glm::vec4 position;
	glm::vec3 normal;
	glm::vec2 texCoord;
};

struct Face
{
	GLuint vertex1;
	GLuint vertex2;
	GLuint vertex3;
};
class Mesh
{
private:
	std::vector<Vertex> vertices;
	
	std::vector<Face> faces;
	GLuint vertexBufferHandle;
	GLuint indexBufferHandle;
	GLuint texture, texture2;
public:
	Mesh();
	~Mesh();
	void loadToBuffer();
	void render(GLuint shaderProgram);
	void addVertex(glm::vec4 position, glm::vec3 normal, glm::vec2 texCoord);
	void addFaces(GLuint vertex1, GLuint vertex2, GLuint vertex3);


};

