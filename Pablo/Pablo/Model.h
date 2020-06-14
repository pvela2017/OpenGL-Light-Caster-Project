#pragma once
#include	<glew.h>
#include	<wglew.h>
#include	<glfw3.h>
#include    <Importer.hpp>      // C++ importer interface
#include    <scene.h>           // Output data structure
#include    <postprocess.h>     // Post processing flags
#include    <windows.h>			// OJO Recien incluidoXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#include    <tchar.h>
#include	<glm/glm.hpp>
#include    <Magick++.h>

#include	<stdlib.h>
#include	<iostream>
#include	<stdio.h>
#include	<string>
#include	<vector>
#include    <fstream>
#include	<tuple>
#include    <wchar.h>		//Recien incluido XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#include    <atlstr.h>

#include "Mesh.h"
#include "Shaders.h"

class Model
{
public:
	bool flag_rot; //flag de rotacion

	// Constructor, expects a filepath to a 3D model.
	Model(GLchar* path);
	GLuint textureID;

	void Draw(Shader shader,GLuint handler);
	void Draw_normal(Shader shader, GLuint handler);

private:
	/*  Model Data  */
	vector<Mesh> meshes;
	string directory;
	vector<Texture> textures_loaded;	// Stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	
	Magick::Image* m_pImage;
	Magick::Blob m_blob;

	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	GLint TextureFromFile(const char* path, string directory);
};