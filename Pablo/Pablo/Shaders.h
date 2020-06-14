#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <sstream>

// GLEW
//#define GLEW_STATIC
#include <glew.h>


// GLFW
#include <glfw3.h>

using std::string;

class Shader
{
public:
	void compileFile(string type, const char * fileName); //compila los shaders
	void linkProgram(void );//Crea porgrama shader y le linkea los shaders
	void Use();
	GLuint Program;

private:	
	GLuint vertexShader;
	GLuint fragmentShader;

	string logString;
	GLint success;
	GLchar infoLog[512];

	bool fileExists(const string & fileName);//verifica que el archivo exista
};