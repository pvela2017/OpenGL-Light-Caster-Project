#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

// GLEW
//#define GLEW_STATIC
#include <glew.h>


// GLFW
#include <glfw3.h>

using std::string;

class Iniventana
{
public:
	Iniventana() {}; //constructor
	int start(GLuint Width, GLuint Height, const char * ventanaName);//Crea ventana

	GLuint Width; //ancho de la ventana
	GLuint Height; //altura de la ventana
	GLFWwindow* idVentana; // puntero de la ventana inicializada atraves de void start
};