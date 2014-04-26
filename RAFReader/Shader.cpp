#include "Shader.h"


Shader::Shader()
{
    
}

Shader::Shader(const char *pathVertex, const char *pathFragment)
{
    load(pathVertex, pathFragment);
}

bool Shader::load(const char *pathVertex, const char *pathFragment)
{
    vertexShaderObj = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderObj = glCreateShader(GL_FRAGMENT_SHADER);
    program = glCreateProgram();

    std::ifstream fileVer;
    std::ifstream fileFrag;

    fileVer.open(pathVertex);

    if(fileVer.is_open())
    {
        std::string buffer;

        while(fileVer.good())
        {
            std::getline(fileVer, buffer);
            vertexSource.append(buffer + "\n");
            
        }

        fileVer.close();
    }
    else
    {
        std::cout << "Cannot open shader file: " << pathVertex << std::endl;
        return false;
    }

    fileFrag.open(pathFragment);
    if(fileFrag.is_open())
    {
        std::string buffer;

        while(fileFrag.good())
        {
            getline(fileFrag, buffer);
            fragmentSource.append(buffer + "\n");
        }
        
        fileFrag.close();
    }
    else
    {
        std::cout << "Cannot open shader file: " << pathFragment << std::endl;
        return false;
    }

    const char *vP = vertexSource.c_str();
    const char *vF = fragmentSource.c_str();

    GLint length = vertexSource.length();

    glShaderSource(vertexShaderObj, 1, &vP, NULL);

   

    glShaderSource(fragmentShaderObj, 1, &vF, NULL);

    glCompileShader(vertexShaderObj);

    GLint Result;
    GLint InfoLogLength;

	glGetShaderiv(vertexShaderObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(vertexShaderObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(vertexShaderObj, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

    glCompileShader(fragmentShaderObj);

	glGetShaderiv(fragmentShaderObj, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(fragmentShaderObj, GL_INFO_LOG_LENGTH, &InfoLogLength);
	std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
	glGetShaderInfoLog(fragmentShaderObj, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
	fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

    glAttachShader(program, vertexShaderObj);
    glAttachShader(program, fragmentShaderObj);

    glLinkProgram(program);

    glDeleteShader(vertexShaderObj);
    glDeleteShader(fragmentShaderObj);

    return true;
}

void Shader::bind()
{
    glUseProgram(program);
}

void Shader::release()
{
    glUseProgram(0);
}

GLuint Shader::getUniformLocation(const char *name)
{
    return glGetUniformLocation(program, name);
}


