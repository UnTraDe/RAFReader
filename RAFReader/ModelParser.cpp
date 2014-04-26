#include "ModelParser.h"

Model ModelFromFiles(char *sknPath, char *sklPath)
{
	Model m = parseSKNFromFile(sknPath);

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
	/*
	for (int i = 0; i < vertices.size(); i++)
	{
		vertices[i].position[2] = -vertices[i].position[2];
	}
	*/
	return Model(vertices, indices);
}

Skeleton parseSKLFromFile(char *path)
{
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char *memory = new char[length];
	file.read(memory, length);
	return parseSKL(memory);
}

Skeleton parseSKL(char *memory)
{
	int position = 0;

	//Read Header

	char id[8];
	memcpy(id, memory + position, sizeof(id));
	position += sizeof(id);

	int version = 0;
	memcpy((char*)&version, memory + position, sizeof(int));
	position += sizeof(int);

	cout << "Reading SKL version: " << version << endl;

	position += sizeof(short); //?

	short numberOfBones = 0;
	memcpy((char*)&numberOfBones, memory + position, sizeof(short));
	position += sizeof(short);

	int numberOfIDs = 0;
	memcpy((char*)&numberOfIDs, memory + position, sizeof(int));
	position += sizeof(int);

	short offsetVertexData = 0;
	memcpy((char*)&offsetVertexData, memory + position, sizeof(short));
	position += sizeof(short);

	position += sizeof(short); //?

	int offetAnimationIndicesV4 = 0;
	memcpy((char*)&offetAnimationIndicesV4, memory + position, sizeof(int));
	position += sizeof(int);

	int offetAnimationIndices = 0;
	memcpy((char*)&offetAnimationIndices, memory + position, sizeof(int));
	position += sizeof(int);
	
	position += sizeof(int); //?
	position += sizeof(int); //?

	int offsetStrings = 0;
	memcpy((char*)&offsetStrings, memory + position, sizeof(int));
	position += sizeof(int);

	position += 20; //Padding? Reserved for future data?

	std::vector<Bone> bones;

	//Read Bones

	int position2 = offsetVertexData;

	for (int i = 0; i < numberOfBones; i++)
	{
		Bone b;

		position2 += sizeof(short); //?

		memcpy((char*)&b.id, memory + position2, sizeof(short));
		position2 += sizeof(short);

		memcpy((char*)&b.parent, memory + position2, sizeof(short));
		position2 += sizeof(short);

		position2 += sizeof(short); //?

		int nameHash = 0;
		memcpy((char*)&nameHash, memory + position2, sizeof(int));
		position2 += sizeof(int);

		position2 += sizeof(float); //?

		memcpy((char*)&b.position[0], memory + position2, sizeof(float));
		position2 += sizeof(float);

		memcpy((char*)&b.position[1], memory + position2, sizeof(float));
		position2 += sizeof(float);

		memcpy((char*)&b.position[2], memory + position2, sizeof(float));
		position2 += sizeof(float);

		position2 += sizeof(float); //?
		position2 += sizeof(float); //?
		position2 += sizeof(float); //?

		memcpy((char*)&b.quaternion[0], memory + position2, sizeof(float));
		position2 += sizeof(float);

		memcpy((char*)&b.quaternion[1], memory + position2, sizeof(float));
		position2 += sizeof(float);

		memcpy((char*)&b.quaternion[2], memory + position2, sizeof(float));
		position2 += sizeof(float);

		memcpy((char*)&b.quaternion[3], memory + position2, sizeof(float));
		position2 += sizeof(float);

		position2 += sizeof(float); //?
		position2 += sizeof(float); //?
		position2 += sizeof(float); //?

		position2 += 32; //Padding maybe?

		bones.push_back(b);
	}

	int position3 = offetAnimationIndicesV4;

	for (int i = 0; i < numberOfBones; i++)
	{
		int sklID = 0;
		memcpy((char*)&sklID, memory + position3, sizeof(int));
		position3 += sizeof(int);

		int anmID = 0;
		memcpy((char*)&anmID, memory + position3, sizeof(int));
		position3 += sizeof(int);

		//Fill the map
	}

	int position4 = offetAnimationIndices;

	std::vector<short> boneIDs;

	for (int i = 0; i < numberOfIDs; i++)
	{
		short boneID = 0;
		memcpy((char*)&boneID, memory + position4, sizeof(short));
		position4 += sizeof(short);

		boneIDs.push_back(boneID);
	}

	int position5 = offsetStrings;

	for (int i = 0; i < numberOfBones; i++)
	{
		char name[32];

		bool foundPadding = false;

		int index = 0;

		while (!foundPadding)
		{
			memcpy(&name[index], memory + position5, 4);
			position5 += 4;

			for (int k = 0; k < 4; k++)
			{
				if (name[index + k] == 0)
				{
					foundPadding = true;
					break;
				}
			}

			index += 4;
		}
		
		bones[i].name;
	}

	//delete memory;

	cout << "Done reading SKL" << endl;

	return Skeleton(bones, boneIDs);
}

Animation parseANMFromFile(char *path)
{
	std::ifstream file(path, std::ios::binary);
	file.seekg(0, file.end);
	int length = file.tellg();
	file.seekg(0, file.beg);
	char *memory = new char[length];
	file.read(memory, length);
	return parseANM(memory);
}

Animation parseANM(char *memory)
{
	int position = 0;

	char magicNumber[8];
	memcpy(magicNumber, memory, sizeof(magicNumber));
	position += sizeof(magicNumber);

	int version = 0;
	memcpy((char*)&version, memory + position, sizeof(int));
	position += sizeof(int);

	cout << "ANM Version " << version << " detected!" << endl;

	Animation anm;

	if (version == 3)
	{
		int designerID = 0;
		memcpy((char*)&designerID, memory + position, sizeof(int));
		position += sizeof(int);
			
		int numberOfBones = 0;
		memcpy((char*)&numberOfBones, memory + position, sizeof(int));
		position += sizeof(int);

		cout << "Number of bones: " << numberOfBones << endl;

		int numberOfFrames = 0;
		memcpy((char*)&numberOfFrames, memory + position, sizeof(int));
		position += sizeof(int);

		int fps = 0;
		memcpy((char*)&fps, memory + position, sizeof(int));
		position += sizeof(int);

		AnimationPos** anim;

		anim = new AnimationPos*[numberOfBones];

		for (int i = 0; i < numberOfBones; i++)
		{
			char name[32];
			memset(name, 0, sizeof(name));
			memcpy(name, memory + position, sizeof(name));
			position += sizeof(name);
			
			cout << name << endl;

			int flag;
			memcpy((char*)&flag, memory + position, sizeof(int));
			position += sizeof(int);

			/*
			int nameHash;
			memcpy((char*)&nameHash, memory + position, sizeof(int));
			position += sizeof(int);
			*/

			anim[i] = new AnimationPos[numberOfFrames];

			for (int j = 0; j < numberOfFrames; j++)
			{
				AnimationPos aPos;
				memcpy((char*)&aPos, memory + position, sizeof(AnimationPos));
				position += sizeof(AnimationPos);
				anim[i][j] = aPos;
			}

			anm = Animation(anim, numberOfBones, numberOfFrames);
		}
	}
	else
	{
		cout << "Unkown version " << version << " detected!" << endl;
	}

	cout << "Done reading ANM" << endl;

	return anm;
}