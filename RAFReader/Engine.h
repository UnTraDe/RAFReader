#pragma once

#include <iostream>
#include <string>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SOIL.h>
#include "Shader.h"
#include "Model.h"
#include "ModelParser.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGH 600

class Engine
{
public:
	Engine();
	~Engine();

	void Initialize();
	void Run();

private:
	void Update(float deltaTime);
	void Render();

	GLFWwindow* m_window;
	Shader m_defaultShader;

	//Temp
	std::shared_ptr<Model> m;
	GLuint mstextureID;
};