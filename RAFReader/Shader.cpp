#include "Shader.h"


Shader::Shader()
{

}

Shader::Shader(const char* pathVertex, const char* pathFragment)
{
	LoadFromFile(pathVertex, pathFragment);
}

bool Shader::LoadFromFile(const char *pathVertex, const char *pathFragment)
{
	m_VertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
	m_FragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
	m_Program = glCreateProgram();
	std::ifstream fileVer;
	std::ifstream fileFrag;
	fileVer.open(pathVertex);

	if (fileVer.is_open())
	{
		std::string buffer;

		while (fileVer.good())
		{
			std::getline(fileVer, buffer);
			m_VertexSource.append(buffer + "\n");

		}

		fileVer.close();
	}
	else
	{
		std::cout << "Cannot open shader file: " << pathVertex << std::endl;
		return false;
	}

	fileFrag.open(pathFragment);

	if (fileFrag.is_open())
	{
		std::string buffer;

		while (fileFrag.good())
		{
			getline(fileFrag, buffer);
			m_FragmentSource.append(buffer + "\n");
		}

		fileFrag.close();
	}
	else
	{
		std::cout << "Cannot open shader file: " << pathFragment << std::endl;
		return false;
	}

	const char *vP = m_VertexSource.c_str();
	const char *vF = m_FragmentSource.c_str();

	glShaderSource(m_VertexShaderObj, 1, &vP, NULL);
	glCompileShader(m_VertexShaderObj);
	GLint Result;
	GLint InfoLogLength;
	glGetShaderiv(m_VertexShaderObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_VertexShaderObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(m_VertexShaderObj, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	printf("Shader (Vertex): %s\n", &VertexShaderErrorMessage[0]);

	glShaderSource(m_FragmentShaderObj, 1, &vF, NULL);
	glCompileShader(m_FragmentShaderObj);
	glGetShaderiv(m_FragmentShaderObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(m_FragmentShaderObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	VertexShaderErrorMessage = std::vector<char>(InfoLogLength);
	glGetShaderInfoLog(m_FragmentShaderObj, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
	printf("Shader (Fragment): %s\n", &VertexShaderErrorMessage[0]);
	
	glAttachShader(m_Program, m_VertexShaderObj);
	glAttachShader(m_Program, m_FragmentShaderObj);
	glLinkProgram(m_Program);
	glDeleteShader(m_VertexShaderObj);
	glDeleteShader(m_FragmentShaderObj);
	return true;
}

void Shader::Bind()
{
	glUseProgram(m_Program);
}

void Shader::Release()
{
	glUseProgram(0);
}

GLuint Shader::GetUniformLocation(const char *name)
{
	GLuint loc = glGetUniformLocation(m_Program, name);

	if (loc == -1)
		printf("Cannot find uniform location: %s \n", name);

	return loc;
}