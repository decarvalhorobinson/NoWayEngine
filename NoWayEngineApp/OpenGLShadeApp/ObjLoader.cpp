#include "ObjLoader.h"

Mesh* ObjLoader::fromFile(std::string path)
{
	Mesh* mesh;

	std::vector<uint> vertexIndices;
	std::vector<uint> uvIndices;
	std::vector<uint> normalIndices;
	std::vector<glm::vec4> tmpVertices;
	std::vector<glm::vec3> tmpNormals;
	std::vector<glm::vec2> tmpUvs;

	FILE* file = fopen(path.c_str(), "r");

	if(file == NULL)
	{
		std::cout << "Couldn't open the file!" << std::endl;
		return nullptr;
	}

	while(true)
	{
		char lineIdentifier[128];
		int res = fscanf(file, "%s", lineIdentifier);
		if(res == EOF)
			break;

		if(strcmp(lineIdentifier, "v") == 0)
		{
			glm::vec4 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			vertex.w = 1.0f;
			tmpVertices.push_back(vertex);
		}else if(strcmp(lineIdentifier, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tmpUvs.push_back(uv);
		}else if(strcmp(lineIdentifier, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tmpNormals.push_back(normal);
		}else if(strcmp(lineIdentifier, "f") == 0)
		{
			uint vertex_index[3];
			uint uv_index[3];
			uint normal_index[3];

			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertex_index[0], &uv_index[0], &normal_index[0], &vertex_index[1], &uv_index[1], &normal_index[1], &vertex_index[2], &uv_index[2], &normal_index[2] );

			if(matches != 9)
			{
				std::cout << "Can't parse .obj file." << std::endl;
				return nullptr; 
			}
		
			
		    
			vertexIndices.push_back(vertex_index[0]);
			vertexIndices.push_back(vertex_index[1]);
		    vertexIndices.push_back(vertex_index[2]);

		    uvIndices.push_back(uv_index[0]);
		    uvIndices.push_back(uv_index[1]);
		    uvIndices.push_back(uv_index[2]);

		    normalIndices.push_back(normal_index[0]);
		    normalIndices.push_back(normal_index[1]);
		    normalIndices.push_back(normal_index[2]);

			

		    
		}
	}
	mesh = new Mesh();
	assert(vertexIndices.size() == uvIndices.size() && uvIndices.size() == normalIndices.size());
	for (int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];

		glm::vec4 vertex = tmpVertices[vertexIndex - 1];

		unsigned int normalIndex = normalIndices[i];

		glm::vec3 normal = tmpNormals[normalIndex - 1];

		unsigned int uvIndex = uvIndices[i];

		glm::vec2 uv = tmpUvs[uvIndex - 1];

		mesh->addVertex(vertex, normal, uv);
		if ((i%3) == 0) 
		{
			mesh->addFaces(i, i+1, i+2);
		}


	}
	return mesh;
}
