/*
Pr�ctica 7: Iluminaci�n 1 
*/
//para cargar imagen

// Este comentario S� se enviar� a main


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

//para iluminaci�n
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
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

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};

	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


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
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	calcAverageNormals(indices, 12, vertices, 32, 8, 5);

	calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);

}


void CreateShaders()
{
	Shader *shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void CrearOctaedro() {
	unsigned int  octaedroIndices[] = {
		0, 3, 17, //Dado 2
		7, 2, 18, //Dado 3
		6, 1, 19, //Dado 4
		5, 4, 16, //Dado 1

		12, 13, 23, //Dado 8
		8, 11, 20, //Dado 5
		10, 15, 21, //Dado 6
		9, 14, 22, //Dado 7

	};

	GLfloat octaedroVertices[] = {
		0.5f,-0.5f,0.5f,	0.0029f,  0.3984f,		0.0f,	-1.0f,	-1.0f,		//A	0	Dado 2
		0.5f,-0.5f,-0.5f,	0.6611f,  0.0049f,		0.0f,	-1.0f,	1.0f,		//B	1	Dado 4
		-0.5f,-0.5f,-0.5f,	0.6611f,  0.3984f,		1.0f,	-1.0f,	0.0f,		//C	2	Dado 3
		-0.5f,-0.5f,0.5f,	0.3330f,  0.5957f,		0.0f,	-1.0f,	-1.0f,		//D	3	Dado 2

		0.5f,-0.5f,0.5f,	0.0029f,  0.3984f,		-1.0f,	-1.0f,	-1.0f,		//A	4	Dado 1
		0.5f,-0.5f,-0.5f,	0.0039f,  0.0049f,		-1.0f,	-1.0f,	-1.0f,		//B	5	Dado 1
		-0.5f,-0.5f,-0.5f,	0.6611f,  0.3984f,		0.0f,	-1.0f,	1.0f,		//C	6	Dado 4
		-0.5f,-0.5f,0.5f,	0.3330f,  0.5957f,		1.0f,	-1.0f,	0.0f,		//D	7	Dado 3

		0.5f,-0.5f,0.5f,	0.3369f,  0.9902f,		0.0f,	1.0f,	-1.0f,		//A	8	Dado 5
		0.5f,-0.5f,-0.5f,	0.9922f,  0.5986f,		0.0f,	1.0f,	1.0f,		//B	9	Dado 7
		-0.5f,-0.5f,-0.5f,	0.6641f,  0.4043f,		1.0f,	1.0f,	0.0f,		//C	10	Dado 6
		-0.5f,-0.5f,0.5f,	0.3369f,  0.6094f,		0.0f,	1.0f,	-1.0f,		//D	11	Dado 5

		0.5f,-0.5f,0.5f,	0.9961f,  0.6094f,		-1.0f,	1.0f,	-1.0f,		//A	12	Dado 8
		0.5f,-0.5f,-0.5f,	0.9961f,  0.9932f,		-1.0f,	1.0f,	-1.0f,		//B	13	Dado 8
		-0.5f,-0.5f,-0.5f,	0.6689f,  0.4043f,		0.0f,	1.0f,	1.0f,		//C	14	Dado 7
		-0.5f,-0.5f,0.5f,	0.3418f,  0.5996f,		-1.0f,	1.0f,	0.0f,		//D	15	Dado 6

		0.0f,0.5f,0.0f,		0.3350f,  0.2002f,		-1.0f,	-1.0f,	-1.0f,		//E	16 Dado 1
		0.0f,0.5f,0.0f,		0.3350f,  0.2002f,		0.0f,	-1.0f,	-1.0f,		//E	17 Dado 2
		0.0f,0.5f,0.0f,		0.3350f,  0.2002f,		1.0f,	-1.0f,	0.0f,		//E	18 Dado 3
		0.0f,0.5f,0.0f,		0.3350f,  0.2002f,		0.0f,	-1.0f,	1.0f,		//E	19 Dado 4

		0.0f,-1.5f,0.0f,	0.6641f,  0.7949f,		0.0f,	1.0f,	-1.0f,		//F	20 Dado 5
		0.0f,-1.5f,0.0f,	0.6641f,  0.7949f,		1.0f,	1.0f,	0.0f,		//F	21 Dado 6
		0.0f,-1.5f,0.0f,	0.6641f,  0.7949f,		0.0f,	1.0f,	1.0f,		//F	22 Dado 7
		0.0f,-1.5f,0.0f,	0.6641f,  0.7949f,		-1.0f,	1.0f,	-1.0f,		//F	23 Dado 8

	};
	Mesh* octaedro = new Mesh();
	octaedro->CreateMesh(octaedroVertices, octaedroIndices, 192, 24);
	meshList.push_back(octaedro);
}

int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	octaDadoTexture = Texture("Textures/octaDado.jpg");
	octaDadoTexture.LoadTexture();


	muro = Model();
	cerberusOrb = Model();
	maurice = Model();

	maurice.LoadModel("Models/maurice.obj");
	cerberusOrb.LoadModel("Models/cerberusOrb.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, s�lo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;

	//Declaraci�n de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		-6.0f, 1.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	//Lampara
	PointLight lamp = PointLight(1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,
		6.0f, 4.0f, 10.0f,
		0.3f, 0.2f, 0.1f);


	// Orbe
	PointLight orb = PointLight(.92f, 0.62f, .031f,
		1.0f, 1.0f,
		0.0f, 5.0f, 0.0f,
		0.3f, 0.2f, 0.1f);
	
	unsigned int spotLightCount = 0;
	//Linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//Luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;

	//Luz cofre
	SpotLight luzCofre = SpotLight(1.0f, 1.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	

	//Spotlight Frontal
	SpotLight farosFrontal = SpotLight(0.0f, 0.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);

	//Spotligh trasero
	SpotLight farosTrasero=SpotLight(1.0f, 0.0f, 0.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	

	

	//se crean mas luces puntuales y spotlight 
	int contPointLights = pointLightCount;
	int contSpotLights = spotLightCount;
	int farosArrayPos=0;
	int luzCofreArrayPos = 0;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
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
		
		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//Spotlights
		//Faros
		if (mainWindow.getFarosFrontal()) {
			spotLights[contSpotLights] = farosFrontal;
			farosArrayPos = contSpotLights;
			contSpotLights++;
		}
		else {
			spotLights[contSpotLights] = farosTrasero;
			farosArrayPos = contSpotLights;
			contSpotLights++;
		}

		//Luz cofre
		if (mainWindow.getmueveCofre() != 0.0f) {
			spotLights[contSpotLights] = luzCofre;
			luzCofreArrayPos = contSpotLights;
			contSpotLights++;
		}

		//Mover faros
		if (mainWindow.getFarosFrontal()) {
			glm::vec3 carPos = glm::vec3(10.0f, 0.1f, -2.0f + mainWindow.getmuevex() / 4);
			glm::vec3 lightDir = glm::vec3(0.0f, 0.0f, 1.0f);
			spotLights[farosArrayPos].SetFlash(carPos, lightDir);
		}
		else {
			glm::vec3 carPos2 = glm::vec3(10.0f, 0.1f, -5.0f + mainWindow.getmuevex() / 4);
			glm::vec3 lightDir2 = glm::vec3(0.0f, 0.0f, -1.0f);
			spotLights[farosArrayPos].SetFlash(carPos2, lightDir2);
		}

		//Mover luz cofre
		if (mainWindow.getmueveCofre() != 0.0f) {
			glm::vec3 cofrePos = glm::vec3(10.0f, 0.1f, -1.0f + mainWindow.getmuevex() / 4);
			glm::vec3 cofreDir = glm::vec3(0.0f, -sin(glm::radians(mainWindow.getmueveCofre())), cos(glm::radians(mainWindow.getmueveCofre())));
			spotLights[luzCofreArrayPos].SetFlash(cofrePos, cofreDir);
		}


		//Point Lights
		//Lampara
		if (mainWindow.getFlashlight()) {
			pointLights[contPointLights] = lamp;
			contPointLights++;
		}
		
		//Orbe
		if (mainWindow.getOrbLight()) {
			pointLights[contPointLights] = orb;
			contPointLights++;
		}
		
		
		

		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetSpotLights(spotLights, contSpotLights);
		shaderList[0].SetPointLights(pointLights, contPointLights);



		//Modelos
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelauxCuerpo(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		
		//Orbe
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cerberusOrb.RenderModel();

		//Maurice
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 15.0f, 0.0));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		maurice.RenderModel();


		//Muro Frente
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(12.0f, 5.0f, 15.f));
		model = glm::scale(model, glm::vec3(2.f, 3.05f, 1.f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, .0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		muro.RenderModel();



	
		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
