/*
Práctica 7: Iluminación 1 
*/
//para cargar imagen
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
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

#include "test.h"
const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture octaDadoTexture;


Model cerberusOrb;
Model muro;
Model maurice;
Model minos;
Model idol;
Model feedbacker;
Model cerberus;
Model venas;
Model corazonMinos;
Model terminal;

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


//función de calculo de normales por promedio de vértices 
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

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	GLfloat calleVertices[] = {
	-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, -10.0f,	5.0f, 0.0f,	0.0f, -1.0f, 0.0f,
	-10.0f, 0.0f, 10.0f,	0.0f, 70.0f,	0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, 10.0f,		5.0f, 70.0f,	0.0f, -1.0f, 0.0f
	};


	
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh *obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh *obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(calleVertices, floorIndices, 32, 6);
	meshList.push_back(obj4);

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

	brickTexture = Texture("Textures/calle.jpg");
	brickTexture.LoadTextureA();
	pisoTexture = Texture("Textures/grass.jpg");
	pisoTexture.LoadTextureA();


	muro = Model();
	cerberusOrb = Model();
	maurice = Model();
	minos = Model();
	idol = Model();
	feedbacker = Model();
	cerberus = Model();
	venas = Model();
	corazonMinos = Model();
	terminal = Model();

	terminal.LoadModel("Models/terminal.obj"); 
	corazonMinos.LoadModel("Models/corazon.obj");
	venas.LoadModel("Models/venas.obj");
	cerberus.LoadModel("Models/cerberus.obj");
	feedbacker.LoadModel("Models/feedbacker.obj");
	idol.LoadModel("Models/idol.obj");
	minos.LoadModel("Models/minos.obj");
	maurice.LoadModel("Models/maurice.obj");
	cerberusOrb.LoadModel("Models/cerberusOrb.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/Dia_Right.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Left.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Down.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Up.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Back.jpg");
	skyboxFaces.push_back("Textures/Skybox/Dia_Front.jpg");
	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	
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
	GLfloat sunIntensity = 0.0f;
	GLfloat sunIncrement = 0.00101f;
	GLfloat sunX = 0.3f;
	GLfloat sunY = -1.0f;
	GLboolean isMorning = true;


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
		
		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		//Main Light
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			.1f+sunIntensity, .1f+sunIntensity,
			sunX, sunY, .0f);

		if (isMorning==true) {
			sunIntensity = sunIntensity + sunIncrement;
			if (sunIntensity >= 0.6f) isMorning = false;
		}
		else {
			sunIntensity = sunIntensity - sunIncrement;
			if (sunIntensity <= 0.1f) isMorning = true;
		}
		
		//Spotlights
	
		


		//Point Lights
	
		
		

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetSpotLights(spotLights, contSpotLights);
		shaderList[0].SetPointLights(pointLights, contPointLights);

		
		
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

		
		//Orbe
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cerberusOrb.RenderModel();

		//Terminal
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(7.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		terminal.RenderModel();

		//Maurice
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		maurice.RenderModel();

		//Idol
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-4.0f, 1.0f, 0.0));
		model = glm::scale(model, glm::vec3(2.f, 2.f, 2.f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));

		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		idol.RenderModel();

		//Feedbacker
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 13.0f, 0.0));
		model = glm::scale(model, glm::vec3(20.f, 20.f, 20.f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		feedbacker.RenderModel();



		//Cerberus
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(4.0f, 1.5f, 0.f));
		model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cerberus.RenderModel();


		
		//Minos Prime

		glm::vec3 cameraPos = camera.getCameraPosition();
		glm::vec3 cameraDir = camera.getCameraDirection();

		float angulo = atan2(cameraDir.x, cameraDir.z);

		float distanciaDetras = -7.0f; 
		glm::vec3 posicionModelo = cameraPos - cameraDir * distanciaDetras;
		posicionModelo.y = 0.2f; 

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
