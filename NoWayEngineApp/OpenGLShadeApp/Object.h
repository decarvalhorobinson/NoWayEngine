#pragma once
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Mesh.h"

struct Transformation
{
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 rotation;
};

class Object
{
private:

	Transformation transformation;
	GLuint shaderProgram;
	Mesh* mesh;

public:

	Object();
	~Object();

	void init();
	void render(GLuint shaderProgram);

	void loadMeshFromFile(char* filePath);
	void loadShaderProgramFromFile(char* shaderVertexFilePath, char* shaderFragmentFilePath);

	Transformation getTransformation();
	void setTransformation(Transformation transformation);

	glm::mat4 getModelMatrix();

	GLuint getShaderProgram();
	void setShaderProgram(GLuint shaderProgram);

	Mesh* getMesh();
	void setMesh(Mesh* mesh);


};

