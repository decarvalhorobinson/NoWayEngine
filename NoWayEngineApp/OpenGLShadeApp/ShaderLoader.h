#pragma once
#include <GL/glew.h>
#include <string>
class ShaderLoader
{
public:
	static GLuint loadShader(char* shaderFile, GLenum type);
	static GLuint createShaderProgram(char* vertexShaderFilePath, char* fragmentShaderFilePath);
	static GLuint loadTexture(std::string filenameString, GLenum minificationFilter = GL_LINEAR, GLenum magnificationFilter = GL_LINEAR);
	ShaderLoader();
	~ShaderLoader();
};

