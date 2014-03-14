#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices)
{
	mVertices = vertices;
	mIndices = indices;
	mMatrix = glm::mat4(1.0f);
	mIsTextured = false;
	Initialize();
}

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones)
{
	mVertices = vertices;
	mIndices = indices;
	mBones = bones;
	mMatrix = glm::mat4(1.0f);
	mIsTextured = false;
	Initialize();
}

Model::~Model()
{
	//glDeleteBuffers(1, &mVertexBuffer);
	//glDeleteBuffers(1, &mIndiceBuffer);
}

void Model::Initialize()
{
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*mVertices.size(), &mVertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mIndiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short)*mIndices.size(), &mIndices[0], GL_STATIC_DRAW);
}