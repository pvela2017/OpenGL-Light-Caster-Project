#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include    <scene.h>           // Output data structure
using namespace std;
// GL Includes
#include <glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shaders.h"


struct Vertex {
	// Position
	glm::vec3 Position;
	// Normal
	glm::vec3 Normal;
	// TexCoords
	glm::vec2 TexCoords;
};

struct Texture {
	GLuint id;
	string type;
	aiString path;
};

class Mesh
{
public:
	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);

	//Informacion de los mesh
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	
	void Draw(Shader shader);
	void bufferDestruction();


private:
	/*  Render data  */
	GLuint VAO, VBO, EBO;
	void setupMesh();

};