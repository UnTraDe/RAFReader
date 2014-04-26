#include "Model.h"

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Matrix = glm::mat4(1.0f);
	m_IsTextured = false;
	//Initialize();
}

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Bones = bones;
	m_Matrix = glm::mat4(1.0f);
	m_IsTextured = false;
	//Initialize();
}

Model::Model(std::vector<Vertex> vertices, std::vector<short> indices, std::vector<Bone> bones, GLuint textureID)
{
	m_Vertices = vertices;
	m_Indices = indices;
	m_Bones = bones;
	m_Matrix = glm::mat4(1.0f);
	m_TextureID = textureID;
	m_IsTextured = true;
	//Initialize();
}

Model::~Model()
{
	//glDeleteBuffers(1, &m_Vbo);
	//glDeleteBuffers(1, &m_IndiceBuffer);
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
	glVertexAttribIPointer(1, 1, GL_INT, sizeof(Vertex), (void*)12);    //char boneIndex[4]
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

	std::vector<glm::quat> quaternions;
	std::vector<glm::vec3> positions;

	for (int i = 0; i < m_Bones.size(); i++)
	{	
		glm::quat q;
		q.x = m_Bones[i].quaternion[0];
		q.y = m_Bones[i].quaternion[1];
		q.z = -m_Bones[i].quaternion[2];
		q.w = -m_Bones[i].quaternion[3];

		quaternions.push_back(q);

		glm::vec3 p;
		p.x = m_Bones[i].position[0];
		p.y = m_Bones[i].position[1];
		p.z = -m_Bones[i].position[2];

		positions.push_back(p);
	}

	std::vector<glm::mat4> bones;

	for (int i = 0; i < m_Bones.size(); i++)
	{
		int parentID = m_Bones[i].parent;

		if (parentID == -1)
			continue;

		quaternions[i] = quaternions[parentID] * quaternions[i];

		glm::vec3 p;
		p.x = m_Bones[i].position[0];
		p.y = m_Bones[i].position[1];
		p.z = m_Bones[i].position[2];

		//positions[i] = positions[parentID] + (p * quaternions[parentID]);
		//positions[i] = positions[parentID] + (quaternions[parentID] * p);

		positions[i] = positions[parentID] + glm::rotate(quaternions[parentID], p);
	}


	for (int i = 0; i < m_Bones.size(); i++)
	{
		glm::mat4 transformation = glm::toMat4(quaternions[i]);
		transformation[3] = glm::vec4(positions[i].x, positions[i].y, positions[i].z, 1.0f);
		transformation = glm::inverse(transformation);
		bones.push_back(transformation);
		//bones.push_back(glm::mat4(1.0f));
	}
	
	glUniformMatrix4fv(shader.getUniformLocation("Bones"), 81, GL_FALSE, &bones[0][0][0]);

	if (m_IsTextured)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
		glUniform1i(m_TextureID, 0);
	}
	
	glBindVertexArray(m_Vao);
	glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_SHORT, (void*)0);
}