#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <GL/glew.h>

#include <assert.h>

class Shader
{
public:
	Shader();
	Shader(const char* pathVertex, const char* pathFragment);
	bool LoadFromFile(const char *pathVertex, const char *pathFragment);
	void Bind();
	void Release();
	GLuint GetUniformLocation(const char* name);
	GLuint GetProgram() { return m_Program; }

private:
	GLuint m_Program;
	GLuint m_VertexShaderObj;
	GLuint m_FragmentShaderObj;
	std::string m_VertexSource;
	std::string m_FragmentSource;
};