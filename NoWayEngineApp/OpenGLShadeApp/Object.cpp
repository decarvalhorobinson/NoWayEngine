#include "Object.h"
#include <GLFW/glfw3.h> // GLFW helper library
#include <stdio.h>
// GLM Mathematics
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderLoader.h"
#include <iostream>
#include "ObjLoader.h"

Object::Object()
{
	init();
}

void Object::init()
{
	transformation.position = glm::vec3(0.0f, 0.0f, 0.0f);
	transformation.scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transformation.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
}

Transformation Object::getTransformation()
{
	return transformation;
}

void Object::setTransformation(Transformation transformation)
{
	this->transformation = transformation;
}

glm::mat4 Object::getModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, transformation.position);
	model = glm::scale(model, transformation.scale);
	model = glm::rotate(model, transformation.rotation.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, transformation.rotation.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, transformation.rotation.z, glm::vec3(0, 0, 1));
	return model;

}


GLuint Object::getShaderProgram()
{
	return shaderProgram;
}

void Object::setShaderProgram(GLuint shaderProgram)
{
	this->shaderProgram = shaderProgram;
}

void Object::render(GLuint shaderProgram) 
{
	if (mesh == nullptr) { return; };
	mesh->render(shaderProgram);
}

void Object::loadMeshFromFile(char * filePath)
{
	ObjLoader objLoad;
	mesh = objLoad.fromFile(filePath);
	if (mesh == nullptr) {
		std::cout << "Error to load the mesh";
		return;
	}

	mesh->loadToBuffer();

}

void Object::loadShaderProgramFromFile(char * shaderVertexFilePath, char * shaderFragmentFilePath)
{
	shaderProgram = ShaderLoader::createShaderProgram(shaderVertexFilePath, shaderFragmentFilePath);
}

Object::~Object()
{
}

void Object::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

Mesh * Object::getMesh()
{
	return mesh;
}
