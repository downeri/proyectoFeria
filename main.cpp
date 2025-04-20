#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Skybox.h"

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

#include "ambiente.h"
#include "boliche.h"
#include "dados.h"
#include "dardos.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Mesh*> bowlingMeshList;
std::vector<Shader> shaderList;


std::vector<Model> diceModelsList;
std::vector<Model> dartsModelsList;


std::vector<Model*> bowlingModelsList;
std::vector<Texture*> bowlingTextureList;

Camera camera;

//Texturas
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture pisoBoliche;



Model cerberusOrb;
Model muro;
Model maurice;
Model woodstock;
Model snoopy;
Model snoopyHouse;
Model banca;
Model basura;
Model lampara;
Model minos;
Model idol;
Model feedbacker;
Model cerberus;
Model venas;
Model corazonMinos;
Model terminal;
Model charlieCarpa;
Model mesaDados;
Model arbol;
Model pino;
Model ship;
Model mesaBoliche;
Model standDardos;
Model pikachu;
Model jigglypuff;
Model squirtle;
Model charmander;
Model carpaPokemon;

Model chandelier;



Skybox skybox;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];


SpotLight spotLights[MAX_SPOT_LIGHTS];



// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci�n de calculo de normales por promedio de v�rtices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	unsigned int wallsIndices[] = {
		0, 1, 2,
		0, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	GLfloat calleVertices[] = {
	-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, -10.0f,	5.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	-10.0f, 0.0f, 10.0f,	0.0f, 70.0f,	0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, 10.0f,		5.0f, 70.0f,	0.0f, -1.0f, 0.0f
	};

	GLfloat bowlingFloorVertices[] = {
	-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, -10.0f,	70.0f, 0.0f,	0.0f, -1.0f, 0.0f,
	-10.0f, 0.0f, 10.0f,	0.0f, 70.0f,	0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, 10.0f,		70.0f, 70.0f,	0.0f, -1.0f, 0.0f
	};

	GLfloat bowlingWallsVertices[] = {
	-0.5f, 0.0f, 0.0f,		0.0f, 0.0f,			0.0f, 0.0f, -1.0f,
	0.5f, 0.0f, 0.0f,		50.0f, 0.0f,		0.0f, 0.0f, -1.0f,
	0.5f, 1.0f, 0.0f,		50.0f, 20.0f,		0.0f, 0.0f, -1.0f,
	-0.5f, 1.0f, 0.0f,		0.0f, 20.0f,		0.0f, 0.0f, -1.0f
	};
	
	Mesh *obj0 = new Mesh();
	obj0->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj0);

	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(calleVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(bowlingFloorVertices, floorIndices, 32, 6);
	bowlingMeshList.push_back(obj4);
	meshList.push_back(obj3);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(bowlingWallsVertices, wallsIndices, 32, 6);
	bowlingMeshList.push_back(obj5);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 6.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	//Carga de texturas
	brickTexture = Texture("Textures/calle.jpg");
	brickTexture.LoadTextureA();
	pisoTexture = Texture("Textures/grass.jpg");
	pisoTexture.LoadTextureA();
	pisoBoliche = Texture("Textures/bowlingFloor.jpg");
	pisoBoliche.LoadTextureA();
	bowlingTextureList.push_back(&pisoBoliche);

	//Carga de Modelos

	muro = Model();
	cerberusOrb = Model();
	maurice = Model();
	woodstock = Model();
	snoopy = Model();
	snoopyHouse = Model();
	banca = Model();
	basura = Model();
	lampara = Model();
	minos = Model();
	idol = Model();
	feedbacker = Model();
	cerberus = Model();
	venas = Model();
	corazonMinos = Model();
	terminal = Model();
	chandelier = Model();

	charlieCarpa = Model();
	mesaDados = Model();
	arbol = Model();
	pino = Model();
	ship = Model();
	mesaBoliche = Model();


	carpaPokemon = Model();
	standDardos = Model();
	pikachu = Model();
	jigglypuff = Model();
	squirtle = Model();
	charmander = Model();
	chandelier.LoadModel("Models/chandelier.obj");
	mesaBoliche.LoadModel("Models/mesaBoliche.obj");
	ship.LoadModel("Models/ship.obj");
	terminal.LoadModel("Models/terminal.obj"); 
	corazonMinos.LoadModel("Models/corazon.obj");
	venas.LoadModel("Models/venas.obj");
	cerberus.LoadModel("Models/cerberus.obj");
	feedbacker.LoadModel("Models/feedbacker.obj");
	idol.LoadModel("Models/idol.obj");
	minos.LoadModel("Models/minos.obj");
	maurice.LoadModel("Models/maurice.obj");
	cerberusOrb.LoadModel("Models/cerberusOrb.obj");
	woodstock.LoadModel("Models/Woodstock.obj");
	snoopy.LoadModel("Models/snoopy.obj");
	snoopyHouse.LoadModel("Models/snoopyHouse.obj");
	banca.LoadModel("Models/banca.obj");
	basura.LoadModel("Models/basura.obj");
	lampara.LoadModel("Models/lampara.obj");
	charlieCarpa.LoadModel("Models/carpaCharlie.obj");
	mesaDados.LoadModel("Models/mesaDados.obj");
	arbol.LoadModel("Models/arbol.obj");
	pino.LoadModel("Models/pino.obj");
	standDardos.LoadModel("Models/standDardos.obj");
	pikachu.LoadModel("Models/pikachu.obj");
	jigglypuff.LoadModel("Models/jigglypuff.obj");
	squirtle.LoadModel("Models/squirtle.obj");
	charmander.LoadModel("Models/charmander.obj");
	carpaPokemon.LoadModel("Models/carpaPokemon.obj");

	bowlingModelsList.push_back(&idol);
	bowlingModelsList.push_back(&maurice);
	bowlingModelsList.push_back(&terminal);
	bowlingModelsList.push_back(&mesaBoliche);
	bowlingModelsList.push_back(&chandelier);

	diceModelsList.push_back(charlieCarpa);
	diceModelsList.push_back(mesaDados);

	dartsModelsList.push_back(carpaPokemon);
	dartsModelsList.push_back(standDardos);
	dartsModelsList.push_back(pikachu);
	dartsModelsList.push_back(jigglypuff);
	dartsModelsList.push_back(squirtle);
	dartsModelsList.push_back(charmander);


	//Skybox
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/Dia_Right.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Left.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Down.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Up.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Right.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Left.jpg");
	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	
	//Point Lights
	unsigned int pointLightCount = 0;

	//Spotlights
	unsigned int spotLightCount = 0;

	

	//se crean mas luces puntuales y spotlight 
	int contPointLights = pointLightCount;
	int contSpotLights = spotLightCount;


	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;

	//Variables del sol
	GLfloat sunIntensity = 0.5f;
	GLfloat sunIncrement = 0.0001f;
	GLfloat sunX = 0.3f;
	GLfloat sunY = -1.0f;
	GLboolean isMorning = true;
	GLint activeSkybox = -1;

	GLboolean bowlingActive = false;

	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);
	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		contPointLights = pointLightCount;
		contSpotLights = spotLightCount;
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		glm::vec3 cameraPos = camera.getCameraPosition();
		glm::vec3 cameraDir = camera.getCameraDirection();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//Main Light
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			sunIntensity, sunIntensity,
			sunX, sunY, .0f);

		if (isMorning==true) {
			sunIntensity = sunIntensity + sunIncrement;
			if (sunIntensity >= 0.6f) isMorning = false;
		}
		else {
			sunIntensity = sunIntensity - sunIncrement;
			if (sunIntensity <= 0.05f) isMorning = true;
		}
		
		if (sunIntensity >= 0.0 && sunIntensity < 0.2 && activeSkybox!=0) {
			activeSkybox = 0;
			skyboxFaces[0] = ("Textures/Skybox/Noche_Right.jpg");
			skyboxFaces[1] = ("Textures/Skybox/Noche_Left.jpg");
			skyboxFaces[2] = ("Textures/Skybox/Noche_Up.jpg");
			skyboxFaces[3] = ("Textures/Skybox/Noche_Up.jpg");
			skyboxFaces[4] = ("Textures/Skybox/Noche_Right.jpg");
			skyboxFaces[5] = ("Textures/Skybox/Noche_Left.jpg");
			skybox = Skybox(skyboxFaces);
		} else if (sunIntensity >= 0.2 && sunIntensity < 0.3 && activeSkybox != 1) {
			activeSkybox = 1;
			skyboxFaces[0] = ("Textures/Skybox/Tarde_Right.jpg");
			skyboxFaces[1] = ("Textures/Skybox/Tarde_Left.jpg");
			skyboxFaces[2] = ("Textures/Skybox/Tarde_Up.jpg");
			skyboxFaces[3] = ("Textures/Skybox/Tarde_Up.jpg");
			skyboxFaces[4] = ("Textures/Skybox/Tarde_Right.jpg");
			skyboxFaces[5] = ("Textures/Skybox/Tarde_Left.jpg");
			skybox = Skybox(skyboxFaces);
		} else if (sunIntensity >= 0.3 && sunIntensity <= 0.6 && activeSkybox != 2) {
			activeSkybox = 2;
			skyboxFaces[0] = ("Textures/Skybox/Dia_Right.jpg");
			skyboxFaces[1] = ("Textures/Skybox/Dia_Left.jpg");
			skyboxFaces[2] = ("Textures/Skybox/Dia_Up.jpg");
			skyboxFaces[3] = ("Textures/Skybox/Dia_Up.jpg");
			skyboxFaces[4] = ("Textures/Skybox/Dia_Right.jpg");
			skyboxFaces[5] = ("Textures/Skybox/Dia_Left.jpg");
			skybox = Skybox(skyboxFaces);
		}

		//Spotlights
	
		


		//Point Lights
	
		
		

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetSpotLights(spotLights, contSpotLights);
		shaderList[0].SetPointLights(pointLights, contPointLights);

		if (mainWindow.getOrbLight()) printf("x: %f y: %f z: %f\n", camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		

		//Modelos
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelauxCuerpo(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		//Piso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Calle
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -.9f, 0.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		brickTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[3]->RenderMesh();

		// Elementos de ambiente 
		elementosAmbiente(model, uniformModel, banca, basura, lampara, arbol, pino);
    
		//Piso juego de Dados
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -0.8f, -300.0f));
		model = glm::scale(model, glm::vec3(0.9f, 1.0f, 2.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoBoliche.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		// Juego de Dados
		renderJuegoDados(model, uniformModel, diceModelsList);

		//Piso Juego de Dardos
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-20.0f, -0.8f, -250.0f));
		model = glm::scale(model, glm::vec3(0.9f, 1.0f, 2.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		pisoBoliche.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();

		// Juego de Dardos
		renderJuegoDardos(model, uniformModel, dartsModelsList);
		
		
	
		//Barco
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(100.0f, 30.0f, 0.0));
		model = glm::scale(model, glm::vec3(50.f, 50.f, 40.f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ship.RenderModel();


		//Maurice NPC
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 60.0));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		maurice.RenderModel();

		
		//Boliche TP
		if (cameraPos.x > 87.82 && cameraPos.x < 110.13 && cameraPos.z < 101.43 && cameraPos.z > -109.71 && cameraPos.y == 6.0) {
			bowlingActive = true;
			camera.teleport(glm::vec3(0.0f, -114.0f, 0.0f));
		}

		if (cameraPos.x < -69.0f || cameraPos.x > 63.0f && cameraPos.z > 57.0f || cameraPos.z < -53.0f && cameraPos.y < 0.0) {
			bowlingActive = false;
			camera.teleport(glm::vec3(0.0f, 6.0f, 0.0f));
		}

		if(bowlingActive) renderBoliche(model, uniformModel, bowlingModelsList, bowlingMeshList, bowlingTextureList);

		//Transparentes
		//Minos Prime Avatar

		float angulo = atan2(cameraDir.x, cameraDir.z);

		float distanciaDetras = -7.0f; 
		glm::vec3 posicionModelo = cameraPos - cameraDir * distanciaDetras;
		posicionModelo.y = cameraPos.y-5.8f; 

		// Venas
		model = glm::mat4(1.0f);
		model = glm::translate(model, posicionModelo);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		model = glm::rotate(model, angulo, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		venas.RenderModel();
		

		//Corazon
		model = glm::translate(model, glm::vec3(0.0f, -.85f, -0.033f));
		model = glm::rotate(model, glm::radians(90.f), glm::vec3(1.0f, 0.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		corazonMinos.RenderModel();
		

		//Cuerpo
		model = modelaux;
		model = glm::translate(model, glm::vec3(0.0f, -0.15f, 0.033f));
		model = glm::scale(model, glm::vec3(1.15f, 1.15f, 1.15f));
		model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0f, 0.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		minos.RenderModel();
		glDisable(GL_BLEND);


		
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
