#include "plano.h"



void Plano::Cargar()
{
	glBindVertexArray(planeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

GLint Plano::TextureFromFile(const char* path)
{

	//GLuint textureID;
	glGenTextures(1, &textureID);
	int width, height;
	try {
		m_pImage = new Magick::Image(path);
		m_pImage->write(&m_blob, "RGBA");
	}
	catch (...) {//Magick::Error& Error
		std::cout << "Error con carga de imagen desde disco" << std::endl;
		return false;
	}
	//unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)m_pImage->columns(), (GLsizei)m_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_blob.data());
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	//SOIL_free_image_data(image);
	return textureID;
}