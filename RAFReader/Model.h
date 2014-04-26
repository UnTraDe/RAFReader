#pragma once

#include <vector>
#include <GL/glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Objects.h"
#include "Shader.h"
#include "Animation.h"
#include "Skeleton.h"

class Model
{
public:
	Model(std::vector<Vertex> vertices, std::vector<short> indices);
	Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones);
	Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones, GLuint textureID);
	~Model();

	void ApplyTexture(GLuint texture) { m_TextureID = texture; m_IsTextured = true; };
	void SetBones(std::vector<Bone> bones) { m_Bones = bones; }
	void Render(const glm::mat4& projection, const glm::mat4& view, Shader& shader);
	void SetAnimation(Animation* animation) { m_Animation = animation; };
	void SetSkeleton(Skeleton* skeleton) {
		m_Bones = skeleton->m_Bones;
		m_BoneIDs = skeleton->m_BoneIDs;

		for (int i = 0; i < m_Vertices.size(); i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_Vertices[i].boneIndex[j] = m_BoneIDs[(int)m_Vertices[i].boneIndex[j]];
			}
			
		}
		Initialize();
	};
	
private:
	std::vector<Vertex> m_Vertices;
    std::vector<short> m_Indices;
	std::vector<Bone> m_Bones;
	std::vector<short> m_BoneIDs;
	
	std::vector<glm::quat> quaternions;
	std::vector<glm::vec3> positions;

	glm::mat4 m_Matrix;

	GLuint m_Vao;
	GLuint m_Vbo;
	GLuint m_IndiceBuffer;
	GLuint m_TextureID;

	bool m_IsTextured;

	Animation* m_Animation;

	void Initialize();
};