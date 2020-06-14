#include "Shaders.h"

using std::ifstream;
using std::ios;
using std::cout;
using std::ostringstream;



void Shader::compileFile(string type, const char * fileName)
{
	if (type == "vertex")//compila los shaders de vertices
	{
		vertexShader = glCreateShader(GL_VERTEX_SHADER);//crea

		if (!fileExists(fileName))//revisa si hay error
		{
			logString = "File not found.";
			printf("%s File Not Found", fileName);
		}

		ifstream inFile(fileName, ios::in);
		if (!inFile) {
			printf("Problem with %s inFile", fileName);
		}

		else
			std::cout << fileName << " Loaded" << std::endl;

		
		ostringstream code;
		while (inFile.good()) {
			int c = inFile.get();
			//std::cout << (char)c;
			if (!inFile.eof()) code << (char)c;
		}
		inFile.close();
		
		string precodigo = code.str();// se guarda como string
		const char * codigo = precodigo.c_str(); //mas strings 
		

		glShaderSource(vertexShader, 1, &codigo, NULL);//obtiene la fuente
		glCompileShader(vertexShader);//compila el shader de vertices


		 //Verifica que no hayan errores en la compilacion
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

	}

	if (type == "fragment")//compila los shaders de fragmentos
	{
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //crea
		

		if (!fileExists(fileName))//revisa si hay error
		{
			logString = "File not found.";
			printf("%s File Not Found", fileName);
		}

		ifstream inFile(fileName, ios::in);
		if (!inFile) {
			printf("Problem with %s inFile", fileName);
		}

		else
			std::cout << fileName << " Loaded" << std::endl;


		ostringstream code;
		while (inFile.good()) {
			int c = inFile.get();
			//std::cout << (char)c;
			if (!inFile.eof()) code << (char)c;
		}
		inFile.close();

		string precodigo = code.str();// se guarda como string
		const char * codigo = precodigo.c_str(); //mas strings 

		glShaderSource(fragmentShader, 1, &codigo, NULL); //obtiene la fuente
		glCompileShader(fragmentShader);//compila el shader de fragmento


		//Verifica que no hayan errores en la compilacion
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

	}
}

void Shader::linkProgram(void )
{
	Program = glCreateProgram();//Crea programa shader
	glAttachShader(Program, vertexShader);//amarra los shaders de vertex
	glAttachShader(Program, fragmentShader);//amarra los shaders de fragment
	glLinkProgram(Program);//linkea los shaders


	// Verifica que no hayan errores en el linkeo
	glGetProgramiv(Program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(Program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);//elimina el shader pues ya no es necesario
	glDeleteShader(fragmentShader);//elimina el shader pues ya no es necesario

}

void Shader::Use()
{
	glUseProgram(Program);
}

bool Shader::fileExists(const string & fileName)
{
	struct stat info;
	int ret = -1;

	ret = stat(fileName.c_str(), &info);
	return 0 == ret;
}

