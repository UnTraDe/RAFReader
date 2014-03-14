#pragma once

#include <glm\glm.hpp>
#include <glm\ext.hpp>
#include "Model.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void RenderModel(Model *model);
	void SetViewMatrix(glm::mat4 &view) { mView = view; };
private:
	glm::mat4 mProjection;
	glm::mat4 mView;
	Shader mShader;

	GLuint test;

};


