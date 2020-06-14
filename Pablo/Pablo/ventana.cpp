#include "ventana.h"

int Iniventana::start(GLuint Width, GLuint Height, const char * ventanaName)
{
	GLFWwindow* idVentana = glfwCreateWindow(Width, Height, ventanaName, nullptr, nullptr); //Crea ventana dimesiones, nombre
	this->idVentana=idVentana;

	//comprueba que la ventana se haya creado bien
	if (this->idVentana == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(this->idVentana); //inicia contexto de opengl

	glewExperimental = GL_TRUE;// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions 
	if (glewInit() != GLEW_OK)// Initialize GLEW to setup the OpenGL Function pointers
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	return 0;
}

