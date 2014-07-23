#include "ModelParser.h"

std::shared_ptr<Model> ModelParser::ParseModel(std::string filePath)
{
	std::ifstream file(filePath.c_str(), std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char *memory = new char[length];
	file.read(memory, length);
	return ParseModel(memory);
}

std::shared_ptr<Model> ModelParser::ParseModel(const char* memory)
{
	unsigned short position = 0;

	/* Read Header */
	int magicNumber = *((int*)&memory[0]);
	short numberOfObjects = *((int*)&memory[4]);
	short containsMaterials = *((int*)&memory[6]);

	/* Read materials  */

	int numberOfMaterials = -1;
	
	if (containsMaterials == 1)
	{
		numberOfMaterials = *((int*)&memory[8]);
		position = 12;

		for (int i = 0; i < numberOfMaterials; i++)
		{
			char nameOfMaterial[64];
			memcpy(nameOfMaterial, &memory[position], sizeof(nameOfMaterial));
			position += sizeof(nameOfMaterial);

			int startVertex = *((int*)&memory[position]);
			position += sizeof(int);
			int numberOfVertices = *((int*)&memory[position]);
			position += sizeof(int);
			int startIndex = *((int*)&memory[position]);
			position += sizeof(int);
			int numberOfIndices = *((int*)&memory[position]);
			position += sizeof(int);
		}
	}

	/* Read total indices and vertices count */

	int totalIndices = *((int*)&memory[position]);;
	position += sizeof(int);

	int totalVertices = *((int*)&memory[position]);;
	position += sizeof(int);

	/* Read indices */

	short *_indices;
	_indices = new short[totalIndices];
	memcpy(_indices, &memory[position], totalIndices * 2);
	position += totalIndices * 2;

	std::vector<short> indices(_indices, _indices + totalIndices);

	/* Read vertices */

	Vertex *_vertices;
	_vertices = new Vertex[totalVertices];
	memcpy(_vertices, &memory[position], totalVertices * sizeof(Vertex));
	position += totalVertices * sizeof(Vertex);	
	std::vector<Vertex> vertices(_vertices, _vertices + totalVertices);

	return std::shared_ptr<Model>(new Model(vertices, indices));
}