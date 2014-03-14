#include "ModelParser.h"

Model ModelFromFiles(char *sknPath, char *sklPath)
{
	Model m = parseSKNFromFile(sknPath);
	m.SetBones(parseSKLFromFile(sklPath));
	return m;
}

Model parseSKNFromFile(char *path)
{
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char *memory = new char[length];
	file.read(memory, length);
	return parseSKN(memory);
}

Model parseSKN(char *memory)
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
	
	return Model(vertices, indices);
}

std::vector<Bone> parseSKLFromFile(char *path)
{
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char *memory = new char[length];
	file.read(memory, length);
	return parseSKL(memory);
}

std::vector<Bone> parseSKL(char *memory)
{
	int position = 0;

	//Read Header

	char version[8];
	memcpy(version, memory + position, sizeof(version));
	position += sizeof(version);

	int numberOfObjects = 0;
	memcpy((char*)&numberOfObjects, memory + position, sizeof(int));
	position += sizeof(int);

	int skeletonHash = 0;
	memcpy((char*)&skeletonHash, memory + position, sizeof(int));
	position += sizeof(int);

	int numberOfElements = 0;
	memcpy((char*)&numberOfElements, memory + position, sizeof(int));
	position += sizeof(int);

	std::vector<Bone> bones;

	//Read Bones

	for (int i = 0; i < numberOfElements; i++)
	{
		Bone b;

		char boneName[32];
		memcpy(boneName, memory + position, sizeof(boneName));
		position += sizeof(boneName);

		memcpy((char*)&b.parent, memory + position, sizeof(int));
		position += sizeof(int);

		memcpy((char*)&b.scale, memory + position, sizeof(float));
		position += sizeof(float);

		memcpy((char*)&b.matrix, memory + position, sizeof(b.matrix));
		position += sizeof(b.matrix);

		bones.push_back(b);
	}

	return bones;
}

void parseANMFromFile(char *path)
{
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char *memory = new char[length];
	file.read(memory, length);
	return parseANM(memory);
}

void parseANM(char *memory)
{
	int position = 0;

	char magicNumber[8];
	memcpy(magicNumber, memory, sizeof(magicNumber));
	position += sizeof(magicNumber);

	int version = 0;
	memcpy((char*)&version, memory + position, sizeof(int));
	position += sizeof(int);

	if (version == 3)
	{
		int designerID = 0;
		memcpy((char*)&designerID, memory + position, sizeof(int));
		position += sizeof(int);
			
		int numberOfBones = 0;
		memcpy((char*)&numberOfBones, memory + position, sizeof(int));
		position += sizeof(int);

		int numberOfFrames = 0;
		memcpy((char*)&numberOfFrames, memory + position, sizeof(int));
		position += sizeof(int);


		int fps = 0;
		memcpy((char*)&fps, memory + position, sizeof(int));
		position += sizeof(int);


		for (int i = 0; i < numberOfBones; i++)
		{
			char name[32];
			memcpy(name, memory + position, sizeof(name));
			position += sizeof(name);
			
			int flag;
			memcpy((char*)&flag, memory + position, sizeof(int));
			position += sizeof(int);

			int nameHash;
			memcpy((char*)&nameHash, memory + position, sizeof(int));
			position += sizeof(int);


			for (int j = 0; j < numberOfFrames; j++)
			{
				AnimationPos aPos;
				memcpy((char*)&aPos, memory + position, sizeof(AnimationPos));
				position += sizeof(AnimationPos);
			}
		}
	}
	else
	{
		cout << "version " << version << " detected!" << endl;
	}
}