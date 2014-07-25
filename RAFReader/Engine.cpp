#include "Engine.h"

Engine::Engine()
{

}

Engine::~Engine()
{
	glfwTerminate();
}

void Engine::Initialize()
{
	/* Initialze Libraries */

	if (!glfwInit())
		std::cout << "Error initializing GLFW" << std::endl;

	m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, "3D Model Animated Test", NULL, NULL);

	if (!m_window)
	{
		glfwTerminate();
		std::cout << "Error creating GLFW window" << std::endl;
	}

	glfwMakeContextCurrent(m_window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error initializing GLEW" << std::endl;

	/* Initialize OpenGL */

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glClearColor(0.4f, 0.596f, 1.0f, 1.0f);

	/* Load Shaders */

	m_defaultShader.LoadFromFile("resources/shaders/vertex.vert", "resources/shaders/fragment.frag");

	/* Load Models */

	m = ModelParser::ParseModel(std::string("resources/Ahri_Skin04.skn"));
	mstextureID = SOIL_load_OGL_texture("resources/Ahri_Skin04_TX_CM.dds", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	m->ApplyTexture(mstextureID);
}

void Engine::Run()
{
	while (!glfwWindowShouldClose(m_window))
	{
		Update(0.0f); //TODO calculate the real deltaTime
		Render();
		glfwSwapBuffers(m_window);
		glfwPollEvents();
	}
}

void Engine::Update(float deltaTime)
{

}

void Engine::Render()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glm::mat4 projection = glm::perspective(45.0f, (float)WINDOW_WIDTH / WINDOW_HEIGH, 0.1f, 1000.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 200.0f, 100.0f), glm::vec3(0.0f, 90.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	m->Render(projection, view, m_defaultShader);
}