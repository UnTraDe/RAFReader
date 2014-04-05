#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Matrix = glm::mat4(1.0f);
	m_IsTextured = false;
	Initialize();
}

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Bones = bones;
	m_Matrix = glm::mat4(1.0f);
	m_IsTextured = false;
	Initialize();
}

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones, GLuint textureID)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Bones = bones;
	m_Matrix = glm::mat4(1.0f);
	m_TextureID = textureID;
	m_IsTextured = true;
	Initialize();
}

Model::~Model()
{
	//glDeleteBuffers(1, &mVertexBuffer);
	//glDeleteBuffers(1, &mIndiceBuffer);
}

void Model::Initialize()
{
	glGenBuffers(1, &m_Vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*m_Vertices.size(), &m_Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m_IndiceBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndiceBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(short)*m_Indices.size(), &m_Indices[0], GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_Vao);
	glBindVertexArray(m_Vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  //float position[3]
	glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, sizeof(Vertex), (void*)12);    //char boneIndex[4]
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16); //float weights[4]
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32); //float normals[3]
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)44); //float textureCords[2]

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndiceBuffer);

	glBindVertexArray(0);
}

void Model::Render(const glm::mat4& projection, const glm::mat4& view, Shader& shader)
{
	shader.bind();

	glm::mat4 model(1.0f);

	glm::mat4 MVP = projection * view * model;
	glUniformMatrix4fv(shader.getUniformLocation("MVP"), 1, GL_FALSE, &MVP[0][0]);

	if (m_IsTextured)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glUniform1i(m_TextureID, 0);
	}
	

	glBindVertexArray(m_Vao);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}