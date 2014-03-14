#pragma once
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Shader 
{
public:
    Shader();
    Shader(const char *pathVertex, const char *pathFragment);
    bool load(const char *pathVertex, const char *pathFragment);
    void bind();
    void release();
    GLuint getUniformLocation(const char *name);

private:
    GLuint program;
    GLuint vertexShaderObj;
    GLuint fragmentShaderObj;
    std::string vertexSource;
    std::string fragmentSource;
};
