#pragma once
#include    <Magick++.h>

#include	<glew.h>
#include	<wglew.h>
#include	<glfw3.h>
#include	<glm/glm.hpp>
#include	<stdlib.h>
#include	<iostream>
#include	<stdio.h>
#include	<string>
#include	<vector>
#include    <fstream>


class Skybox
{
public:
	//Constructor
	//Skybox(GLchar* path);


	GLuint loadCubemap(void); // Carga el skybox
	void mapLoader(void);
	void vaoyvbo(void);
	std::vector<const GLchar*> facess;
	
	GLuint skyboxVAO;


private:
	GLuint textureID;
	int width= 1960, height= 1080;
	Magick::Blob image;

	Magick::Image* m_pImage;
	Magick::Blob m_blob;
	std::vector<Magick::Blob> faces;
	

	std::string directory;
	std::string filename;

	GLuint skyboxVBO;

	
	
	GLfloat skyboxVertices[108] = {
		// Posiciones        
		-100.0f,  100.0f, -100.0f,
		-100.0f, -100.0f, -100.0f,
		 100.0f, -100.0f, -100.0f,
		 100.0f, -100.0f, -100.0f,
		 100.0f,  100.0f, -100.0f,
		-100.0f,  100.0f, -100.0f,

		-100.0f, -100.0f,  100.0f,
		-100.0f, -100.0f, -100.0f,
		-100.0f,  100.0f, -100.0f,
		-100.0f,  100.0f, -100.0f,
		-100.0f,  100.0f,  100.0f,
		-100.0f, -100.0f,  100.0f,

		 100.0f, -100.0f, -100.0f,
		 100.0f, -100.0f,  100.0f,
		 100.0f,  100.0f,  100.0f,
		 100.0f,  100.0f,  100.0f,
		 100.0f,  100.0f, -100.0f,
		 100.0f, -100.0f, -100.0f,

		-100.0f, -100.0f,  100.0f,
		-100.0f,  100.0f,  100.0f,
		 100.0f,  100.0f,  100.0f,
		 100.0f,  100.0f,  100.0f,
		 100.0f, -100.0f,  100.0f,
		-100.0f, -100.0f,  100.0f,

		-100.0f,  100.0f, -100.0f,
		 100.0f,  100.0f, -100.0f,
	  	 100.0f,  100.0f,  100.0f,
		 100.0f,  100.0f,  100.0f,
		-100.0f,  100.0f,  100.0f,
		-100.0f,  100.0f, -100.0f,

		-100.0f, -100.0f, -100.0f,
		-100.0f, -100.0f,  100.0f,
		 100.0f, -100.0f, -100.0f,
		 100.0f, -100.0f, -100.0f,
		-100.0f, -100.0f,  100.0f,
		 100.0f, -100.0f,  100.0f
	};

};