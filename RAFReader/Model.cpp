#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices)
{
	m_vertices = vertices;
	m_indices = indices;
	m_matrix = glm::mat4(1.0f);
	m_isTextured = false;
	Initialize();
}

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices, GLuint textureID)
{
	m_vertices = vertices;
	m_indices = indices;
	m_matrix = glm::mat4(1.0f);
	m_textureID = textureID;
	m_isTextured = true;
	Initialize();
}

Model::~Model()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_indiceBuffer);
}

void Model::ApplyTexture(GLuint texture)
{ 
	m_textureID = texture;
	m_isTextured = true;
}

void Model::Initialize()
{
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_indiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short)*m_indices.size(), &m_indices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  //float position[3]
	glVertexAttribIPointer(1, 1, GL_INT, sizeof(Vertex), (void*)12);    //char boneIndex[4]
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16); //float weights[4]
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32); //float normals[3]
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)44); //float textureCords[2]

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indiceBuffer);

	glBindVertexArray(0);
}

void Model::Render(const glm::mat4& projection, const glm::mat4& view, Shader& shader)
{
	shader.Bind();

	glm::mat4 model(1.0f);

	glm::mat4 MVP = projection * view * model;
	glUniformMatrix4fv(shader.GetUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);
	
	if (m_isTextured)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
		glUniform1i(m_textureID, 0);
	}
	
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}