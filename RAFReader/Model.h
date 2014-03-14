#pragma once

#include <GL/glew.h>
#include <gl/GL.h>
#include <glm\glm.hpp>
#include <vector>
#include "Objects.h"

class Model
{
public:
	Model(std::vector<Vertex> vertices, std::vector<short> indices);
	Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones);
	~Model();

	void ApplyTexture(GLuint texture) { mTextureID = texture; mIsTextured = true; };

	void SetBones(std::vector<Bone> bones) { mBones = bones; }

	glm::mat4 GetMatrix() { return mMatrix; }
	GLuint GetVertexBuffer() { return mVertexBuffer; }
	GLuint GetIndiceBuffer() { return mIndiceBuffer; }
	int GetIndiceSize() { return mIndices.size(); }
	GLuint GetTexture() { return mTextureID; };
	bool IsTextured() { return mIsTextured; };
	
private:
	std::vector<Vertex> mVertices;
    std::vector<short> mIndices;
	std::vector<Bone> mBones;
	
	glm::mat4 mMatrix;

	GLuint mVertexBuffer;
	GLuint mIndiceBuffer;
	GLuint mTextureID;

	bool mIsTextured;

	void Initialize();
};