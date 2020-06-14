#pragma once
#include <vector>
#include <iostream>
#include <Magick++.h>

#include	<stdlib.h>
#include	<iostream>
#include	<stdio.h>
#include	<string>

// GL Includes
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Plano
{
public:
	GLuint textureID;
	Plano(const char* path)
	{
		this->directory = std::string(path).substr(0, std::string(path).find_last_of('/'));
		glGenVertexArrays(1, &planeVAO);
		glGenBuffers(1, &planeVBO);
		glBindVertexArray(planeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glBindVertexArray(0);
		textureID=TextureFromFile(path);
	}
	void Cargar();

private:
	GLint TextureFromFile(const char* path);
	std::string directory;
	GLuint planeVAO;
	GLuint planeVBO;
	
	Magick::Image* m_pImage;
	Magick::Blob m_blob;

	GLfloat planeVertices[48] = {
		// Positions            // Normals           // Texture Coords
		10.0f, -0.5f,  10.0f,  0.0f,  1.0f,  0.0f,  10.0f, 0.0f,
		-10.0f, -0.5f, -10.0f,  0.0f,  1.0f,  0.0f,  0.0f,  10.0f,
		-10.0f, -0.5f,  10.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

		10.0f, -0.5f,  10.0f,  0.0f,  1.0f,  0.0f,  10.0f, 0.0f,
		10.0f, -0.5f, -10.0f,  0.0f,  1.0f,  0.0f,  10.0f, 10.0f,
		-10.0f, -0.5f, -10.0f,  0.0f,  1.0f,  0.0f,  0.0f,  10.0f
	};
};