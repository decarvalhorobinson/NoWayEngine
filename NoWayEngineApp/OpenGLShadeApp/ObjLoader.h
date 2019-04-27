#include <string>
#include <iostream>
#include "Mesh.h"

/* File reading from C is faster */
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <glm/glm.hpp>
#include <vector>

typedef float GLfloat;
typedef unsigned int uint;



class ObjLoader
{
public:
	Mesh* fromFile(std::string path);
};

