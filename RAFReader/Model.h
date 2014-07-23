#pragma once

#include <vector>
#include <GL/glew.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Objects.h"
#include "Shader.h"

class Model
{
public:
	Model(std::vector<Vertex> vertices, std::vector<short> indices);
	Model(std::vector<Vertex> vertices, std::vector<short> indices, GLuint textureID);
	~Model();

	void ApplyTexture(GLuint texture);
	void Render(const glm::mat4& projection, const glm::mat4& view, Shader& shader);
	
private:
	std::vector<Vertex> m_vertices;
    std::vector<short> m_indices;
	glm::mat4 m_matrix;
	GLuint m_vao;
	GLuint m_vbo;
	GLuint m_indiceBuffer;
	GLuint m_textureID;
	bool m_isTextured;

	void Initialize();
};