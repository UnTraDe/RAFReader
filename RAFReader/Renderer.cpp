#include "Renderer.h"

Renderer::Renderer()
{
	mProjection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
	mShader.load("shaders/vertex.vert", "shaders/fragment.frag");

	GLuint vertexID;
	glGenVertexArrays(1, &vertexID);
	glBindVertexArray(vertexID);
}

void Renderer::RenderModel(Model *model)
{	
	mShader.bind();
	
	glm::mat4 MVP = mProjection * mView * model->GetMatrix();
	glUniformMatrix4fv(mShader.getUniformLocation("MVP") , 1, GL_FALSE, &MVP[0][0]);

	if (model->IsTextured())
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, model->GetTexture());
		glUniform1i(model->GetTexture(), 0);
	}
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);

	glBindBuffer(GL_ARRAY_BUFFER, model->GetVertexBuffer());
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);  //float position[3]
	glVertexAttribPointer(1, 1, GL_INT, GL_FALSE, sizeof(Vertex), (void*)12);    //char boneIndex[4]
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)16); //float weights[4]
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)32); //float normals[3]
	glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)44); //float textureCords[2]

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->GetIndiceBuffer());

	glDrawElements(GL_TRIANGLES, model->GetIndiceSize(), GL_UNSIGNED_SHORT, (void*)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(4);
	
}