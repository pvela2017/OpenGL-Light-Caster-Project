#include "main.h"


using namespace irrklang;

ISoundEngine *SoundEngine = createIrrKlangDevice();

// Function prototypes
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void Do_Movement();

//Opciones
Camara Cam1(glm::vec3(0.0f, 3.0f, 10.0f));
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
bool keysPressed[1024];
bool keys[1024];

// Delta
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

//momentaneo
GLfloat ejey=0, ejex = -0, ejez = 0.0f;
GLdouble x=0.0, y = 0.0, z = 0.0;
bool sp = false;
bool en_helice = false;
bool music = false;
GLfloat angulo =45.0f;
GLboolean shadows = true;

glm::vec3 des;
glm::vec3 P0 = {0.0f,0.0f,0.0f};
glm::vec3 P1 = { 0.0f,100.0f,0.0f };
glm::vec3 P2 = { 100.0f,100.0f,0.0f };
glm::vec3 P3 = { 100.0f,0.0f,0.0f };
float vel = 0.001f;
float t = 0.0f;



// The MAIN function
int main()
{

	std::cout << "Starting GLFW context, OpenGL 4.4" << std::endl;
	
	glfwInit(); // Se inicioa GLFW
	// Se configuran las opciones de GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//version del opengl a ocupar 4.X
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);//version del opengl a ocupar X.4
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// especifica la compatibilidad del opengl core/es
	glfwWindowHint(GLFW_RESIZABLE, GLU_FALSE); //no permite que se pueda cambiar el tamano

	// Crea  GLFWwindow object para GLFW's functions con la clase ventana
	Iniventana vent1;
	vent1.Width = 1200;//1960;
	vent1.Height = 800;// 1080;
	vent1.start(vent1.Width, vent1.Height,"prueba");//Crea ventana dimesiones, nombre


	const GLubyte* version = glGetString(GL_VERSION);// Obtiene versión de OpenGL
	if (version == 0)
	{
		std::cout << "Error en obtener version de OpenGL" << std::endl;
	}
	else {
		std::cout << "Version = " << version << std::endl;
	}

	//Callbacks
	glfwSetKeyCallback(vent1.idVentana, key_callback); // teclado
	glfwSetScrollCallback(vent1.idVentana, scroll_callback); //scroll mouse
	glfwSetCursorPosCallback(vent1.idVentana, mouse_callback);//mouse

	glfwSetInputMode(vent1.idVentana, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//Opciones de OpenGL
	glEnable(GL_DEPTH_TEST);

	// Define the viewport dimensions
	glViewport(0, 0, vent1.Width, vent1.Height); // especifica desde que punto (x,y) se renderizara y hasta donde

	//Compilacion de shaders
	Shader programaShader;
	programaShader.compileFile("vertex","C:/Pablo/shaderPrograms/sivi.vert");// Lee el archivo y lo describe en un string en memoria
	programaShader.compileFile("fragment", "C:/Pablo/shaderPrograms/sivi.frag");// Lee el archivo y lo describe en un string en memoria
	programaShader.linkProgram(); //se linkean los shaders

	/*Shader skybox;
	skybox.compileFile("vertex", "C:/Pablo/shaderPrograms/skybox.vert");// Lee el archivo y lo describe en un string en memoria
	skybox.compileFile("fragment", "C:/Pablo/shaderPrograms/skybox.frag");// Lee el archivo y lo describe en un string en memoria
	skybox.linkProgram(); //se linkean los shaders*/

	Shader sombra;
	sombra.compileFile("vertex", "C:/Pablo/shaderPrograms/depth_map.vert");// Lee el archivo y lo describe en un string en memoria
	sombra.compileFile("fragment", "C:/Pablo/shaderPrograms/depth_map.frag");// Lee el archivo y lo describe en un string en memoria
	sombra.linkProgram(); //se linkean los shaders


	//Modelos
	Model Avion("C:/Pablo/Spitfire_unido/spit.3ds");

	/*//Skybox
	Skybox caras;
	caras.vaoyvbo();
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/right.jpg");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/left.jpg");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/top.jpg");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/bottom.jpg");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/back.jpg");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/front.jpg");
	//cubo2
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/hills_rt.tga");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/hills_lf.tga");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/hills_up.tga");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/hills_dn.tga");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/hills_bk.tga");
	caras.facess.push_back("C:/Pablo/cubemap/ely_hills/hills_ft.tga");
	caras.mapLoader();
	GLuint cubemapTexture=caras.loadCubemap();*/

	//FRAMEBUFFER
	// Configure depth map FBO
	const GLuint SHADOW_WIDTH = 7000, SHADOW_HEIGHT = 7000;
	GLuint depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);
	// - Create depth texture
	GLuint depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	GLfloat borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		std:cout << "ERROR DEPTH BUFFER" << std::endl;
	}
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);


	//GLSL
	GLuint viewLocation = glGetUniformLocation(programaShader.Program, "view");
	GLuint projectiontLocation = glGetUniformLocation(programaShader.Program, "projection");
	GLuint modelLocation = glGetUniformLocation(programaShader.Program, "model");

	//GLuint rotLocation = glGetUniformLocation(programaShader.Program, "rot"); //matriz de rotacion
	//GLuint trans_idalLocation = glGetUniformLocation(programaShader.Program, "trans_ida"); //matriz de ida
	//GLuint trans_vueltalLocation = glGetUniformLocation(programaShader.Program, "trans_vuelta"); //matriz de vuelta

	GLuint pos_luz = glGetUniformLocation(programaShader.Program, "lightPos");
	GLuint pos_vis = glGetUniformLocation(programaShader.Program, "viewPos");
	GLuint matriz_luz = glGetUniformLocation(programaShader.Program, "lightSpaceMatrix");
	GLuint sombras = glGetUniformLocation(programaShader.Program, "shadows");
	GLuint difusse_location= glGetUniformLocation(programaShader.Program, "diffuseTexture");
	GLuint shadowMap_location = glGetUniformLocation(programaShader.Program, "shadowMap");

	GLuint matriz_sombra = glGetUniformLocation(sombra.Program, "lightSpaceMatrix");
	GLuint model_sombra = glGetUniformLocation(sombra.Program, "model");

	programaShader.Use();
	glUniform1i(difusse_location, 0);
	glUniform1i(shadowMap_location, 1);

	//Matrices
	glm::mat4 rota;
	glm::mat4 trans_ida;
	glm::mat4 trans_vuelta;
	glm::mat4 lightSpaceMatrix;
	glm::vec3 viewPos;
	glm::mat4 Camview;
	glm::mat4 projection;
	glm::mat4 lightView;
	glm::mat4 lightProjection;

	glm::mat4 model;
	glm::mat4 model1;

	// Light source
	glm::vec3 lightPos(-10.0f, 500.0f, -5.0f);


	//Plano
	Plano piso("C:/Pablo/montanas/metal.png");

	auto Bezier = [](glm::vec3 P0, glm::vec3 P1, glm::vec3 P2, glm::vec3 P3, float velocidad,float t)
	{
		glm::vec3 pos;
		pos.x = P0.x*(1.0f - t)*(1.0f - t)*(1.0f - t) + 3.0f*P1.x*t*(1.0f - t)*(1.0f - t) + 3.0f * P2.x*t *t * (1.0f - t) + P3.x*t*t*t;
		pos.y = P0.y*(1.0f - t)*(1.0f - t)*(1.0f - t) + 3.0f*P1.y*t*(1.0f - t)*(1.0f - t) + 3.0f * P2.y*t *t * (1.0f - t) + P3.y*t*t*t;
		pos.z = P0.z*(1.0f - t)*(1.0f - t)*(1.0f - t) + 3.0f*P1.z*t*(1.0f - t)*(1.0f - t) + 3.0f * P2.z*t *t * (1.0f - t) + P3.z*t*t*t;
		std::cout << pos.x << "/ " << pos.y << "/ " << pos.z << std::endl;
		return pos;
	};

	//loop
	while (!glfwWindowShouldClose(vent1.idVentana))
	{
		// Set frame time
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();//revisa si sucedieron eventos, apretaron teclas etc
		Do_Movement();

		//sombra1
		lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 1000.0f);
		lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(1.0f));
		lightSpaceMatrix = lightProjection * lightView;

		sombra.Use();
		glUniformMatrix4fv(matriz_sombra, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
		glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
		glClear(GL_DEPTH_BUFFER_BIT);//se limpian el buffer de color y el de profundida
		//Renderizar modelos aqui para sombras
		//piso
		model = glm::mat4();
		glUniformMatrix4fv(model_sombra, 1, GL_FALSE, glm::value_ptr(model));
		piso.Cargar();
		//avion1
		model1 = glm::mat4();
		model1 = glm::translate(model1, glm::vec3(-1.0f, 2.0f, 2.0));
		model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(model_sombra, 1, GL_FALSE, glm::value_ptr(model1));
		Avion.Draw_normal(sombra,sombra.Program);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);


		//RENDERIZADO NORMAL
		glViewport(0, 0, vent1.Width, vent1.Height);// Reset viewport
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//se limpian el buffer de color y el de profundida
		programaShader.Use();
		//camara
		projection = glm::perspective(Cam1.Zoom, (float)vent1.Width / (float)vent1.Height, 0.1f, 100.0f);//1000.0 por defecto
		Camview = Cam1.GetViewMatrix();

		glUniformMatrix4fv(projectiontLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(Camview));
		glUniform3fv(pos_luz, 1, &lightPos[0]);
		glUniform3fv(pos_vis, 1, &Cam1.Position[0]);
		glUniformMatrix4fv(matriz_luz, 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glUniform1i(shadows, sombras);

		//glClearColor(0.396f, 0.537f, 0.835f, 1.0f);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, piso.textureID);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		//renderizar modelos aqui
		//piso
		model = glm::mat4();
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, &model[0][0]);
		piso.Cargar();
		//avion
		model1 = glm::mat4();
		model1 = glm::translate(model1, glm::vec3(-1.0f, 2.0f, 2.0));
		model1 = glm::rotate(model1, glm::radians(45.0f), glm::vec3(-1.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model1));
		Avion.Draw_normal(programaShader, programaShader.Program);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap);

		/*model = glm::translate(model, glm::vec3(ejex, ejez, ejey)); 

		//spline
		if (sp)
		{
			des = Bezier(P0, P1, P2, P3, vel,t);
			t += 0.01f;
		}
		model = glm::translate(model, des);

		//model = glm::scale(model, glm::vec3(400.2f, 400.2f, 400.2f));	//dimensiones spit (20.2f, 20.2f, 20.2f)
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		//helice
		trans_ida = glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, 2.115f, 0.0f));
		trans_vuelta = glm::translate(glm::dmat4(1.0f), glm::dvec3(0.0f, -2.115f, 0.0f));
		rota = glm::rotate(glm::mat4(1.0f), glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(trans_idalLocation, 1, GL_FALSE, &trans_ida[0][0]);
		glUniformMatrix4fv(trans_vueltalLocation, 1, GL_FALSE, &trans_vuelta[0][0]);
		glUniformMatrix4fv(rotLocation, 1, GL_FALSE, &rota[0][0]);
		
		//encendido helice
		if (en_helice)
		{
			angulo += 100.0f;
			if (music)
			{
				SoundEngine->play2D("C:/Pablo/Pablo/x64/Release/start1.mp3", GL_TRUE);
			}
			music = false;
		}


		
		//Avion.Draw(programaShader,programaShader.Program);

		/*
		//Cargar skybox
		glDepthFunc(GL_LEQUAL);
		skybox.Use();
		//view = glm::mat4(glm::mat3(Cam1.Vista()));
		glUniformMatrix4fv(glGetUniformLocation(skybox.Program, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skybox.Program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glBindVertexArray(caras.skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glUniform1i(glGetUniformLocation(skybox.Program, "skybox"), 0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);*/

		glfwSwapBuffers(vent1.idVentana); //swapea el buffer de atras con el de adelante
	}
	
	//programaShader.bufferDestruction();//se eliminan los buffers creados
	glfwTerminate();// Terminate GLFW, clearing any resources allocated by GLFW.
	return 0;
}




// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key <= 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
			keysPressed[key] = false;
		}
	}

	if (key == GLFW_KEY_LEFT )//mueve izq
		Cam1.Position.x += 100.0f;

	if (key == GLFW_KEY_RIGHT )//mueve dere
		Cam1.Position.x -= 100.0f;

	if (key == GLFW_KEY_UP )//mueve arriba
		Cam1.Position.y += 100.0f;

	if (key == GLFW_KEY_DOWN )//mueve abajo
		Cam1.Position.y -= 100.0f;

	if (key == GLFW_KEY_X)//giro 
	{
		angulo += 1.0f;

	}

	if (key == GLFW_KEY_O && action == GLFW_PRESS)//spline
	{
		sp = true;

	}

	if (key == GLFW_KEY_U )//helice
	{
		en_helice = true;
		music = true;

	}

	if (key == GLFW_KEY_J)//helice
	{
		en_helice = false;
		SoundEngine->stopAllSounds();

	}

	if (key==GLFW_KEY_SPACE && action==GLFW_KEY_SPACE)
	{
		shadows = !shadows;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	Cam1.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Cam1.ProcessMouseScroll(yoffset);
}

void Do_Movement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		Cam1.ProcessKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		Cam1.ProcessKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		Cam1.ProcessKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		Cam1.ProcessKeyboard(RIGHT, deltaTime);

	if (keys[GLFW_KEY_SPACE] && !keysPressed[GLFW_KEY_SPACE])
	{
		shadows = !shadows;
		keysPressed[GLFW_KEY_SPACE] = true;
	}



}