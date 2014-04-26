#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <SOIL.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>
#include <glm/glm.hpp>
#include "RAFManager.h"
#include "ModelParser.h"
#include "Shader.h"
#include "Camera.h"
#include "Config.h"
#include "Animation.h"
/*
#pragma comment(lib, "zlibstat.lib")
#pragma comment(lib, "libboost_filesystem-vc110-mt-gd-1_50.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "SOIL.lib")
*/
#define CAMERA_SPEED 1.0f

using namespace std;

void update();

Camera camera;
GLFWwindow* window;

int main(int argc, char const *argv[])
{
    if (!glfwInit())
        return -1;

	window = glfwCreateWindow(800, 600, "Model Viewer", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
	
	glfwMakeContextCurrent(window);

    glewExperimental = true;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    GLuint textureID = SOIL_load_OGL_texture("resources/Ahri_base_TX_CM.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	Model m = parseSKNFromFile("resources/Ahri.skn");
	Skeleton s = parseSKLFromFile("resources/Ahri.skl");
	m.SetSkeleton(&s);
	m.ApplyTexture(textureID);

	Animation anm = parseANMFromFile("resources/Ahri_dance.anm");
	m.SetAnimation(&anm);

	glm::mat4 projection = glm::perspective(45.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);

	//Shader shader("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");
	Shader shader("resources/shaders/animated.vert", "resources/shaders/animated.frag");

	glClearColor(0.4f, 0.596f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m.Render(projection, camera.getView(), shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
	
    return 0;
}

void update()
{
    //Handle inpurt for camera
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.moveAhead(CAMERA_SPEED);

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.moveBack(CAMERA_SPEED);

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.moveLeft(CAMERA_SPEED);

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.moveRight(CAMERA_SPEED);

    int wX;
    int wY;
    glfwGetWindowSize(window, &wX, &wY);

    double x;
    double y;
    glfwGetCursorPos(window, &x, &y);
        
    camera.addVerticalAngle((float(wY / 2) - y) * 0.002f);
    camera.addHorizontalAngle((float(wX / 2) - x) * 0.002f);
    glfwSetCursorPos(window, wX / 2, wY / 2);

    camera.calculateVectors();
}
