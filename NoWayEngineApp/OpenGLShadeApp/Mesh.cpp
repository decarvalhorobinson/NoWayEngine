#include "Mesh.h"
#include "ShaderLoader.h"



Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

void Mesh::loadToBuffer()
{
	glGenBuffers(1, &vertexBufferHandle);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBufferHandle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * faces.size() * sizeof(GLuint), &faces[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	ShaderLoader shaderLoader;
	// Load an image and bind it to a texture
	texture = shaderLoader.loadTexture("Deer_body_D.tga");
	texture2 = shaderLoader.loadTexture("3d_models/farm_house_text.png");
}

/**
	shaderProgram - a shader program with vertexPosition, vertexNormal and vertexTexCoord attributes
*/
void Mesh::render(GLuint shaderProgram)
{
	glBindTexture(GL_TEXTURE_2D, texture2);

	GLuint positionLocation = glGetAttribLocation(shaderProgram, "vertexPosition");
	GLuint normalLocation = glGetAttribLocation(shaderProgram, "vertexNormal");
	GLuint texCoordLocation = glGetAttribLocation(shaderProgram, "vertexTexCoord");
	
	

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferHandle);
	glVertexAttribPointer(positionLocation, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(offsetof(Vertex, position)));
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(offsetof(Vertex, normal)));
	glVertexAttribPointer(texCoordLocation, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(offsetof(Vertex, texCoord)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(positionLocation);
	glEnableVertexAttribArray(normalLocation);
	glEnableVertexAttribArray(texCoordLocation);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferHandle);
	glDrawElements(GL_TRIANGLES, 30 * faces.size(), GL_UNSIGNED_INT, (GLvoid *)0);
	//glDrawElements(GL_TRIANGLES, 3 * faces.size(), GL_UNSIGNED_INT, (GLvoid *)0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisableVertexAttribArray(texCoordLocation);
	glDisableVertexAttribArray(normalLocation);
	glDisableVertexAttribArray(texCoordLocation);


	

}

void Mesh::addVertex(glm::vec4 position, glm::vec3 normal, glm::vec2 texCoord)
{
	Vertex vertex;
	vertex.position = position;
	vertex.normal = normal;
	vertex.texCoord = texCoord;
	this->vertices.push_back(vertex);

}

void Mesh::addFaces(GLuint vertex1, GLuint vertex2, GLuint vertex3)
{
	Face face;
	face.vertex1 = vertex1;
	face.vertex2 = vertex2;
	face.vertex3 = vertex3;
	faces.push_back(face);
}


