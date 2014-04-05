#pragma once

#include <vector>
#include <GL/glew.h>
#include <gl/GL.h>
#include <glm\glm.hpp>
#include "Objects.h"
#include "Shader.h"

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
	
private:
	std::vector<Vertex> m_Vertices;
    std::vector<short> m_Indices;
	std::vector<Bone> m_Bones;
	
	glm::mat4 m_Matrix;

	GLuint m_Vao;
	GLuint m_Vbo;
	GLuint m_IndiceBuffer;
	GLuint m_TextureID;

	bool m_IsTextured;

	void Initialize();
};