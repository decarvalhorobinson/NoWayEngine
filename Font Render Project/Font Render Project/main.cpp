#include<glew\include\GL\glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ft2build.h>
#include <map>
#include "ShaderLoader.h"
#include "vector"
#include "string"
#include <fstream>
// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include FT_FREETYPE_H  
float deltaTime = 0;
float 	lastTime = 0;
FT_Library  library;
FT_Face     face;
std::string texto = "0123456789";
int block = 1;
int isTextChanged = 0;

struct Vertex {
	glm::vec3 position;
	glm::vec3  normal;
	glm::vec2  uv;
};

struct Character {
	float	x;
	float	y;
	float	width;
	float	height;
	float	xoffset;
	float	yoffset;
	float	xadvance;
	float utl, vtl;
	float utr, vtr;
	float ubr, vbr;
	float ubl, vbl;
};

std::map<int, Character> chars;

static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

void loadFont() 
{
	//load the library
	if (FT_Init_FreeType(&library))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	//load the font file
	if (FT_New_Face(library, "C:/Windows/Fonts/Arial.ttf", 0, &face))
	//if (FT_New_Face(library, "testefont.fnt", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	//define the font size
	FT_Set_Pixel_Sizes(face, 0, 48);
	//load a character
	if (FT_Load_Char(face, 'A', FT_LOAD_RENDER))
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
}

void loadFntFile() {
	std::string path = "arial.fnt";
	FILE* file = fopen(path.c_str(), "r");

	if (file == NULL)
	{
		std::cout << "Couldn't open the file!" << std::endl;
		return;
	}

	//create a buffer to skip lines
	char buffer[1000];
	//skip the first line
	fgets(buffer, 1000, file);
	//variable info from the file
	int lineHeight, base, scaleW, scaleH, pages, packed, charsCount;

	fscanf(file, "common lineHeight=%d", &lineHeight);
	fscanf(file, " base=%d", &base);
	fscanf(file, " scaleW=%d", &scaleW);
	fscanf(file, " scaleH=%d", &scaleH);
	fscanf(file, " pages=%d", &pages);
	fscanf(file, " packed=%d\n", &packed);
	//skip the pages
	while (pages) {
		fgets(buffer, 1000, file);
		pages--;
	};
	//read the number of chars
	fscanf(file, "chars count=%d\n", &charsCount);


	std::cout << " lineHeight " << lineHeight
		<< " base " << base 
		<< " scaleW " << scaleW 
		<< " scaleH " << scaleH 
		<< " pages " << pages 
		<< " packed " << packed
		<< " charsCount " << charsCount << "\n";

	while (true)
	{	

		int charId, x, y,width, height, xoffset, yoffset,xadvance,page, chnl;

		int res = fscanf(file, "char id=%d", &charId);
		if (res == EOF || res == 0)
			break;		
		fscanf(file, " x=%d", &x);
		fscanf(file, " y=%d", &y);
		fscanf(file, " width=%d", &width);
		fscanf(file, " height=%d", &height);
		fscanf(file, " xoffset=%d", &xoffset);
		fscanf(file, " yoffset=%d", &yoffset);
		fscanf(file, " xadvance=%d", &xadvance);
		fscanf(file, " page=%d", &page);
		fscanf(file, " chnl=%d\n", &chnl);
		
		Character ch;
		ch.x = (float)x;
		ch.y = (float)y;
		ch.width = (float)width;
		ch.height = (float)height;
		ch.xoffset = (float)xoffset;
		ch.yoffset = (float)yoffset;
		ch.xadvance = (float)xadvance;

		ch.utl = (float)(x) / (float)scaleW;
		ch.vtl = 1-((float)(y) / (float)scaleH);

		ch.utr = (float)(x) / (float)scaleW;
		ch.vtr = 1 - ((float)(y + height) / (float)scaleH);

		ch.ubr = ((float)(x + width) / (float)scaleW);
		ch.vbr = 1 - ((float)(y + height) / (float)scaleH);

		ch.ubl = (float)(x  +width) / (float)scaleW;
		ch.vbl = 1 - (float)(y) / (float)scaleH;

		chars[charId] = ch;


	}

	

}

GLuint installShader() {

	char* path1 = "fragment.glsl";
	std::ifstream in1(path1);
	std::string src1 = "";
	std::string line1 = "";
	while (std::getline(in1, line1))
		src1 += line1 + "\n";



	char* path2 = "vertex.glsl";
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
		return 0;
	}

	glUseProgram(programID);
	return programID;


}

int cursor = 4;
int drawCursor(int index, float x, float y, float scale, std::vector<GLushort>  *indices, std::vector<Vertex>  *vertices, std::map<int, Character> *chars)
{
	Character ch = (*chars)['|'];
	float xpos = x + (ch.xoffset * scale) - (scale * ch.xadvance)/2;
	float ypos = y - (ch.height + ch.yoffset) * scale;

	GLfloat w = ch.width*scale;
	GLfloat h = ch.height*scale;

	Vertex vertex0, vertex1, vertex2, vertex3;
	vertex0.position = glm::vec3(xpos + w, ypos + h, 0.0f);
	vertex1.position = glm::vec3(xpos, ypos + h, 0.0f);
	vertex2.position = glm::vec3(xpos, ypos, 0.0f);
	vertex3.position = glm::vec3(xpos + w, ypos, 0.0f);

	vertex0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	vertex1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	vertex2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
	vertex3.normal = glm::vec3(0.0f, 0.0f, 1.0f);

	float ubl = ch.ubl;
	float vbl = ch.vbl;

	float utl = ch.utl;
	float vtl = ch.vtl;

	float utr = ch.utr;
	float vtr = ch.vtr;

	float ubr = ch.ubr;
	float vbr = ch.vbr;

	vertex0.uv = glm::vec2(ubl, vbl);
	vertex1.uv = glm::vec2(utl, vtl);
	vertex2.uv = glm::vec2(utr, vtr);
	vertex3.uv = glm::vec2(ubr, vbr);

	vertices->push_back(vertex0);
	vertices->push_back(vertex1);
	vertices->push_back(vertex2);
	vertices->push_back(vertex3);
	int offset = index * 4 + 4;
	if(texto.length()<=0)
	{
		offset = 0;
	}



	indices->push_back(0 + offset);
	indices->push_back(1 + offset);
	indices->push_back(2 + offset);

	indices->push_back(2 + offset);
	indices->push_back(3 + offset);
	indices->push_back(0 + offset);
	return (ch.xadvance) * scale;

}
int createText(std::string text, GLfloat x, GLfloat y, GLfloat scale, std::vector<GLushort>  *indices, std::vector<Vertex>  *vertices, std::map<int, Character> *chars, float deltaTime) {
	int teste = (int)(deltaTime * 1000);
	vertices->clear();
	indices->clear();
	
	GLfloat lineBegin = x;
	int created = 0;
	std::vector<Vertex>  *vertices2 = new std::vector<Vertex>();	
	float size = scale;
	int flag = 1;
	int cursorOffset = 0;
	if (teste % 1000 < 500)
	{
		if (text.length() <= 0)
		{
			//cursor
			teste = (int)(deltaTime * 1000);
			if (teste % 1000 < 500)
			{
				if (cursor <= 0 && flag)
				{
					std::cout << "Dentro do = " << cursor << "\n";
					drawCursor(0, x, y, scale, indices, vertices, chars);
					flag = 0;
					created = 1;
				}


			}
		}
		//endCursor
	}
	for (int i = 0; i < text.length(); i++)
	{

		

		Character ch = (*chars)[text[i]];
		if (text[i] == '\n') {
			y -= 50*scale;
			x = lineBegin + ch.xoffset* scale*2;
		}
		GLfloat xpos = x + ch.xoffset* scale;
		GLfloat ypos = y - (ch.height + ch.yoffset) * scale;

		GLfloat w = ch.width*scale;
		GLfloat h = ch.height*scale;
		
		if (teste % 1000 < 500)
		{
			if (cursor <= 0 && flag)
			{
				drawCursor(i - 1, x, y, scale, indices, vertices, chars);
				flag = 0;
				cursorOffset = 4;
			}
		}
	


		Vertex vertex0, vertex1, vertex2, vertex3;
		vertex0.position = glm::vec3(xpos + w, ypos + h, 0.0f);
		vertex1.position =   glm::vec3(xpos, ypos + h, 0.0f);
		vertex2.position =   glm::vec3(xpos, ypos, 0.0f);
		vertex3.position = glm::vec3(xpos + w, ypos, 0.0f);
		
		vertex0.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertex1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertex2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertex3.normal = glm::vec3(0.0f, 0.0f, 1.0f);

		float ubl = ch.ubl;
		float vbl = ch.vbl;

		float utl = ch.utl;
		float vtl = ch.vtl;

		float utr = ch.utr;
		float vtr = ch.vtr;

		float ubr = ch.ubr;
		float vbr = ch.vbr;

		vertex0.uv = glm::vec2(ubl, vbl);
		vertex1.uv = glm::vec2(utl, vtl);
		vertex2.uv = glm::vec2(utr, vtr);
		vertex3.uv = glm::vec2(ubr, vbr);

		vertices->push_back(vertex0);
		vertices->push_back(vertex1);
		vertices->push_back(vertex2);
		vertices->push_back(vertex3);
		int offset = i * 4 + cursorOffset;

		indices->push_back(0 + offset);
		indices->push_back(1 + offset);
		indices->push_back(2 + offset);
	
		indices->push_back(2 + offset);
		indices->push_back(3 + offset);
		indices->push_back(0 + offset);


		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.xadvance) * scale;
		
		//cursor
		if (teste % 1000<500)
		{
			if (((cursor-1) == i || cursor<=0)&& flag)
			{
				drawCursor(i, x, y, scale, indices, vertices, chars);
				flag = 0;
				cursorOffset = 4;
			}
			

		}
		//endCursor





		created = 1;
	};
	return created;
}

void loadTextToBuffer(std::vector<GLushort> *indices, std::vector<Vertex>  *vertices) {
	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);//create the buffer id
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);// bind the buffer with the current type os buffer to use 
	glBufferData(GL_ARRAY_BUFFER, vertices->size() * sizeof(Vertex), &((*vertices)[0]), GL_STATIC_DRAW);// store the data

	glEnableVertexAttribArray(0);// mark the buffer to its attrib 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	glEnableVertexAttribArray(1);// mark the buffer to its attrib 1 location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 3));

	glEnableVertexAttribArray(2);// mark the buffer to its attrib 2 location
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid *)(sizeof(float) * 6));

	GLuint indexBuffer;
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices->size() * sizeof(GLuint), &((*indices)[0]), GL_STATIC_DRAW);
}

void characterCallback(GLFWwindow* window, unsigned int codepoint, int mods)
{

	std::string temp = texto.substr(0, cursor);
	temp += ((char)codepoint);
	texto = temp + texto.substr(cursor, texto.size());

	++cursor;

	isTextChanged = 1;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_BACKSPACE && ((action == GLFW_REPEAT)|| (action == GLFW_PRESS)))
	{
		
		if (cursor <= 0) 
		{
			cursor =0;
		}
		else 
		{
			std::string temp = texto.substr(0, cursor - 1);
			texto = temp + texto.substr(cursor, texto.size());
			--cursor;
		}

	}
	if (key == GLFW_KEY_DELETE && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{

		if (cursor >= texto.length())
		{
			cursor = texto.length();
		}
		else
		{
			std::string temp = texto.substr(0, cursor);
			texto = temp + texto.substr(cursor + 1, texto.size());
		}

	}
	
	if (key == GLFW_KEY_ENTER && (action == GLFW_PRESS))
	{
		std::string temp = texto.substr(0, cursor);
		temp += std::string("\n");
		texto = temp + texto.substr(cursor, texto.size());
		++cursor;
	}
	
	if (key == GLFW_KEY_LEFT && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		--cursor;
		if (cursor <= 0) cursor = 0;
	}

	if (key == GLFW_KEY_RIGHT && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		++cursor;
		if (cursor >= texto.length()) cursor = texto.length();
	}

	if (key == GLFW_KEY_UP && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		std::string temp = texto.substr(0, cursor);
		cursor = temp.rfind("\n");
		temp = texto.substr(0, cursor);
		cursor = temp.rfind("\n");
		cursor++;
		if (cursor <= 0) cursor = 0;
	}

	if (key == GLFW_KEY_DOWN && ((action == GLFW_REPEAT) || (action == GLFW_PRESS)))
	{
		std::string temp = texto.substr(cursor, texto.length());
		cursor += temp.find('\n');
		temp = texto.substr(cursor, texto.length());
		cursor += temp.find('\n') + 1;
		if (cursor >= texto.length() -1 || cursor<=0) cursor = texto.length();
	}

		
}

int main(void)
{
	
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) exit(EXIT_FAILURE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(800, 600, "Simple example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetCharModsCallback(window, characterCallback);
	glfwSetKeyCallback(window, keyCallback);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_MULTISAMPLE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	loadFont();
	loadFntFile();
	ShaderLoader sl;
	GLuint texture = sl.loadTexture("arial.png");
	std::vector<Vertex> *vertices = new std::vector<Vertex>();
	std::vector<GLushort> *indices = new std::vector<GLushort>();
	//createText("Palavra1\nPalavra2\nPalavra3\n", 10.0f, 250.0f, 2.0f, indices, vertices, &chars);
	//loadTextToBuffer(indices, vertices);


	int created = 0;
	while (!glfwWindowShouldClose(window))
	{
		double currentTime = glfwGetTime();
		deltaTime = float(currentTime - lastTime);
		try
		{

			created = (createText(texto, 60.0f, 250.0f, 1.4f, indices, vertices, &chars, deltaTime));
			if (created)
			{
				loadTextToBuffer(indices, vertices);
			}
			isTextChanged = 0;
			float ratio;
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);
			ratio = width / (float)height;
			glViewport(0, 0, 800, 600);
			glClear(GL_COLOR_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);


			glLoadIdentity();
			glOrtho(0.0f, (float)width, (float)height, 0.0f, 0.0f, 0.2f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glLoadIdentity();

			GLuint shaderProgram = installShader();
			glm::mat4 projection = glm::mat4(1.0f);
			projection *= glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -0.01f, 1000.0f);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "mvp"), 1, 0, glm::value_ptr(projection));

			glBindTexture(GL_TEXTURE_2D, texture);
			if (created)
			{
				glDrawElements(GL_TRIANGLES, indices->size() + 1, GL_UNSIGNED_SHORT, (char*)(0));
			}

			glUseProgram(0);
		}
		catch (const std::exception&)
		{

		}

		

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
