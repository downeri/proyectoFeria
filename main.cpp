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
#include "bateo.h"
#include "dados.h"
#include "dardos.h"

//include zim
#include "PuestoGlobosZim.h"
#include "PuestoPizzaZim.h"
#include "PuestoHachaZim.h"
#include "PuestoToposZim.h"


#include "puestoPan.h"
#include "puestoRefrescos.h"
#include "puestoGlobosPokemon.h"
#include "minosPrime.h"
#include "woodstock.h"
#include "pichu.h"
#include "snoopySanta.h"


const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Mesh*> bowlingMeshList;
std::vector<Mesh*> battingMeshList;
std::vector<Shader> shaderList;
std::vector<glm::vec2> messageCoordinates;

std::vector<Model*> diceModelsList;
std::vector<Model*> dartsModelsList;

std::vector<Model*> breadModelsList;
std::vector<Model*> sodaModelsList;
std::vector<Model*> pokemonBalloonsModelsList;

std::vector<Model*> woodstockModelsList;


std::vector<Model*> bowlingModelsList;
std::vector<Model*> battingModelsList;
std::vector<Model*> minosModelsList;
std::vector<Model*> minosVeinsModelsList;

std::vector<Texture*> bowlingTextureList;
std::vector<Texture*> battingTextureList;

std::vector<Camera*> cameraList;

GLfloat bowlingAnimation[7];
GLfloat battingAnimation[4];
GLfloat parryAnimation[4];

Camera camera;
Camera birdsEyeViewCamera;
Camera bowlingCamera;
Camera antojitosCamera;
Camera axesCamera;
Camera sodaCamera;
Camera battingCamera;
Camera baloonCamera;
Camera snoopyHouseCamera;
Camera esquitesCamera;
Camera diceCamera;
Camera pizzaCamera;
Camera dartsCamera;
Camera breadCamera;
Camera whackAMoleCamera;


//Texturas
Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture pisoBoliche;
Texture blackTexture;
Texture battingFloor;
Texture battingWalls;
Texture lavaTexture;
Texture ultrakillFont;




//Models

Model cerberusOrb;
Model muro;
Model maurice;
Model woodstock;
Model alaDerechaWoodstock;
Model alaIzquierdaWoodstock;
Model snoopy;
Model snoopyHouse;
Model snoopySanta;
Model banca;
Model basura;
Model lampara;
Model minos;
Model idol;
Model feedbackerUpper;
Model feedbackerLower;
Model cerberus;
Model venas;
Model corazonMinos;
Model terminal;
Model charlieCarpa;
Model mesaDados;
Model charlieBrown;
Model dado;
Model arbol;
Model pino;
Model ship;
Model mesaBoliche;
Model standDardos;
Model pikachu;
Model jigglypuff;
Model squirtle;
Model charmander;
Model pichu;
Model ash;
Model brock;
Model carpaPokemon;
Model chandelier;
Model mesa;
Model dardo;
Model puestoPan;
Model puestoRefrescos;
Model globosPokemon;
Model bowlingRailing;
Model bowlingLaneFloor;
Model carpet;
Model ultraEsquites;
Model cerberusStatue;
Model bowlingChair;
Model minosVeinsUpperRightArm;
Model minosVeinsUpperLeftArm;
Model minosVeinsRightThigh;
Model minosVeinsRightLeg;
Model minosVeinsLowerLeftArm;
Model minosVeinsLeftThigh;
Model minosVeinsLeftLeg;
Model minosVeinsBody;

Model minosUpperRightArm;
Model minosUpperLeftArm;
Model minosRightThigh;
Model minosRightLeg;
Model minosLowerRightHand;
Model minosLowerLeftArm;
Model minosLeftThigh;
Model minosLeftLeg;
Model minosHead;
Model minosVeinsLowerRightArm;
Model minosBody;

Model rejaBateo;
Model v1Ultrakill;
Model v2Ultrakill;
Model ultrakillFountain;

Model ultrakillDoor;
Model ultrakillArch;

//Modelos zim
Model Puestogloboszim_M;
Model Puestopizzazim_M;
Model Puestohachazim_M;
Model Puestotoposzim_M;
Model NPCGloboszim_M;
Model NPCToposzim_M;
Model NPCPizzazim_M;
Model NPChachazim_M;
Model NPCMartillotoposzim_M;
Model CerditoOjosNorm_M;
Model CerditoOjosX_M;
Model NPCBrazo1pizza_M;
Model NPCOjosabiertos_M;
Model NPCOjoscerrados_M;
Model NPCDibbrazo_M;
Model NPChacha_M;
Model NPCbrazoglobos_M;
Model CasaZim_M;
Model Hachacasazim_M;
Model Hacha2casazim_M;

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
PointLight lucesPuntuales[MAX_POINT_LIGHTS];


SpotLight spotLights[MAX_SPOT_LIGHTS];



// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//funci�n de calculo de normales por promedio de v�rtices 
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount, unsigned int vLength, unsigned int normalOffset)
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
	
	GLfloat battingFloorVertices[] = {
	-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, -10.0f,	30.0f, 0.0f,	0.0f, -1.0f, 0.0f,
	-10.0f, 0.0f, 10.0f,	0.0f, 30.0f,	0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, 10.0f,		30.0f, 30.0f,	0.0f, -1.0f, 0.0f
	};

	GLfloat lavaVertices[] = {
	-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, -10.0f,	2.0f, 0.0f,		0.0f, -1.0f, 0.0f,
	-10.0f, 0.0f, 10.0f,	0.0f, 1.0f,	0.0f, -1.0f, 0.0f,
	10.0f, 0.0f, 10.0f,		2.0f, 1.0f,	0.0f, -1.0f, 0.0f
	};

	GLfloat signVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.01f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.1f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.1f, .9f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.01f, .9f,		0.0f, -1.0f, 0.0f,

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

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(bowlingWallsVertices, wallsIndices, 32, 6);
	bowlingMeshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(battingFloorVertices, floorIndices, 32, 6);
	battingMeshList.push_back(obj6);
	battingMeshList.push_back(obj5);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(lavaVertices, floorIndices, 32, 6);
	battingMeshList.push_back(obj7);

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(signVertices, wallsIndices, 32, 6);
	meshList.push_back(obj8);

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

	//Camaras
	camera = Camera(glm::vec3(0.0f, 6.0f, 170.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 0.6f, 0.5f);
	birdsEyeViewCamera = Camera(glm::vec3(0.0f, 200.0f, 130.0f), glm::vec3(.0f, 0.0f, -1.0f), 0.0f, -90.0f, 0.0f, 0.0f);
	bowlingCamera = Camera(glm::vec3(-50.0f, 50.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	antojitosCamera = Camera(glm::vec3(-.5f, 4.0f, -130.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	axesCamera = Camera(glm::vec3(.5f, 4.0f, -170.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	sodaCamera = Camera(glm::vec3(.5f, 4.0f, -220.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	battingCamera = Camera(glm::vec3(-5.f, 4.0f, -300.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	baloonCamera = Camera(glm::vec3(-5.f, 4.0f, -380.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	baloonCamera = Camera(glm::vec3(-5.f, 4.0f, -380.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, 0.0f, 0.0f, 0.0f);
	snoopyHouseCamera = Camera(glm::vec3(-5.f, 4.0f, -330.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);
	esquitesCamera = Camera(glm::vec3(-5.f, 4.0f, -300.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);
	diceCamera = Camera(glm::vec3(10.f, 4.0f, -250.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);
	pizzaCamera = Camera(glm::vec3(-5.f, 4.0f, -180.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);
	dartsCamera = Camera(glm::vec3(15.f, 4.0f, -130.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);
	breadCamera = Camera(glm::vec3(0.f, 4.0f, -50.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);
	whackAMoleCamera = Camera(glm::vec3(0.f, 4.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), 180.0f, 0.0f, 0.0f, 0.0f);

	cameraList.push_back(&camera);
	cameraList.push_back(&birdsEyeViewCamera);
	cameraList.push_back(&bowlingCamera);
	cameraList.push_back(&antojitosCamera);
	cameraList.push_back(&axesCamera);
	cameraList.push_back(&sodaCamera);
	cameraList.push_back(&battingCamera);
	cameraList.push_back(&baloonCamera);
	cameraList.push_back(&snoopyHouseCamera);
	cameraList.push_back(&esquitesCamera);
	cameraList.push_back(&diceCamera);
	cameraList.push_back(&pizzaCamera);
	cameraList.push_back(&dartsCamera);
	cameraList.push_back(&breadCamera);
	cameraList.push_back(&whackAMoleCamera);

	//Carga de texturas
	brickTexture = Texture("Textures/calle.jpg");
	blackTexture = Texture("Textures/negro.jpg");
	pisoTexture = Texture("Textures/grass.jpg");
	pisoBoliche = Texture("Textures/bowlingFloor.jpg");
	battingFloor = Texture("Textures/floordecoration8b.png");
	battingWalls = Texture("Textures/floorpattern2n.png");
	lavaTexture = Texture("Textures/LavaSingle.png");
	ultrakillFont = Texture("Textures/ultrakillFont.png");
	
	
	
	ultrakillFont.LoadTextureA();
	lavaTexture.LoadTextureA();
	battingWalls.LoadTextureA();
	battingFloor.LoadTextureA();
	brickTexture.LoadTextureA();
	pisoTexture.LoadTextureA();
	pisoBoliche.LoadTextureA();
	blackTexture.LoadTextureA();


	bowlingTextureList.push_back(&pisoBoliche);
	bowlingTextureList.push_back(&blackTexture);

	battingTextureList.push_back(&battingFloor);
	battingTextureList.push_back(&battingWalls);
	battingTextureList.push_back(&lavaTexture);

	//Carga de Modelos

	muro = Model();
	cerberusOrb = Model();
	maurice = Model();
	woodstock = Model();
	alaDerechaWoodstock = Model();
	alaIzquierdaWoodstock = Model();
	snoopy = Model();
	snoopyHouse = Model();
	snoopySanta = Model();
	banca = Model();
	basura = Model();
	lampara = Model();
	minos = Model();
	idol = Model();
	feedbackerUpper = Model();
	feedbackerLower = Model();
	cerberus = Model();
	venas = Model();
	corazonMinos = Model();
	terminal = Model();
	chandelier = Model();

	charlieCarpa = Model();
	mesaDados = Model();
	charlieBrown = Model();
	mesa = Model();

	arbol = Model();
	pino = Model();

	ship = Model();
	mesaBoliche = Model();
	carpet = Model();
	bowlingChair = Model();

	carpaPokemon = Model();
	standDardos = Model();
	pikachu = Model();
	jigglypuff = Model();
	squirtle = Model();
	charmander = Model();
	pichu = Model();
	ash = Model();
	brock = Model();

	dardo = Model();
	mesa = Model();

	puestoPan = Model();
	puestoRefrescos = Model();
	globosPokemon = Model();


	bowlingRailing = Model();
	bowlingLaneFloor = Model();
	ultraEsquites = Model();
	cerberusStatue = Model();
	minosVeinsUpperRightArm = Model();
	minosVeinsUpperLeftArm = Model();
	minosVeinsRightThigh = Model();
	minosVeinsRightLeg = Model();
	minosVeinsLowerLeftArm = Model();
	minosVeinsLeftThigh = Model();
	minosVeinsLeftLeg = Model();
	minosVeinsBody = Model();

	minosUpperRightArm = Model();
	minosUpperLeftArm = Model();
	minosRightThigh = Model();
	minosRightLeg = Model();
	minosLowerRightHand = Model();
	minosLowerLeftArm = Model();
	minosLeftThigh = Model();
	minosLeftLeg = Model();
	minosHead = Model();
	minosVeinsLowerRightArm = Model();
	minosBody = Model();
	rejaBateo = Model();
	v1Ultrakill = Model();
	v2Ultrakill = Model();
	ultrakillFountain = Model();

	ultrakillArch = Model();
	ultrakillDoor = Model();

	ultrakillArch.LoadModel("Models/ultrakillArch.obj");
	ultrakillDoor.LoadModel("Models/ultrakillDoor.obj");
	ultrakillFountain.LoadModel("Models/ultrakillFountain.obj");
	v2Ultrakill.LoadModel("Models/UltraV2.obj");
	v1Ultrakill.LoadModel("Models/UltraV1.obj");
	rejaBateo.LoadModel("Models/reja.obj");
	minosVeinsUpperRightArm.LoadModel("Models/Minos_Veins_Upper_Right_Arm.obj");
	minosVeinsUpperLeftArm.LoadModel("Models/Minos_Veins_Upper_Left_Arm.obj");
	minosVeinsRightThigh.LoadModel("Models/Minos_Veins_Right_Thigh.obj");
	minosVeinsRightLeg.LoadModel("Models/Minos_Veins_Right_Leg.obj");
	minosVeinsLowerLeftArm.LoadModel("Models/Minos_Veins_Lower_Left_Arm.obj");
	minosVeinsLowerRightArm.LoadModel("Models/Minos_Veins_Lower_Right_Arm.obj");
	minosVeinsLeftThigh.LoadModel("Models/Minos_Veins_Left_Thigh.obj");
	minosVeinsLeftLeg.LoadModel("Models/Minos_Veins_Left_leg.obj");
	minosVeinsBody.LoadModel("Models/Minos_Veins_Body.obj");

	minosUpperRightArm.LoadModel("Models/Minos_Upper_Right_Arm.obj");
	minosUpperLeftArm.LoadModel("Models/Minos_Upper_Left_Arm.obj");
	minosRightThigh.LoadModel("Models/minos_right_thigh.obj");
	minosRightLeg.LoadModel("Models/minos_right_leg.obj");
	minosLowerRightHand.LoadModel("Models/Minos_Lower_Right_Hand.obj");
	minosLowerLeftArm.LoadModel("Models/Minos_Lower_Left_Arm.obj");
	minosLeftThigh.LoadModel("Models/Minos_Left_Thigh.obj");
	minosLeftLeg.LoadModel("Models/minos_left_leg.obj");
	minosHead.LoadModel("Models/Minos_Head.obj");
	minosBody.LoadModel("Models/Minos_Body.obj");

	minosRightLeg.LoadModel("Models/Minos_Right_Leg.obj");
	bowlingChair.LoadModel("Models/chair.obj");
	cerberusStatue.LoadModel("Models/cerbStatue.obj");
	ultraEsquites.LoadModel("Models/ultraEsquites.obj");
	carpet.LoadModel("Models/carpet.obj");
	bowlingLaneFloor.LoadModel("Models/bowlingLaneFloor.obj");
	bowlingRailing.LoadModel("Models/railing.obj");

	chandelier.LoadModel("Models/chandelier.obj");
	mesaBoliche.LoadModel("Models/mesaBoliche.obj");
	ship.LoadModel("Models/ship.obj");
	terminal.LoadModel("Models/terminal.obj"); 
	corazonMinos.LoadModel("Models/corazon.obj");
	venas.LoadModel("Models/venas.obj");
	cerberus.LoadModel("Models/cerberus.obj");
	feedbackerLower.LoadModel("Models/feedbackerLower.obj");
	feedbackerUpper.LoadModel("Models/feedbackerUpper.obj");
	idol.LoadModel("Models/idol.obj");
	minos.LoadModel("Models/minos.obj");
	maurice.LoadModel("Models/maurice.obj");
	cerberusOrb.LoadModel("Models/cerberusOrb.obj");
	woodstock.LoadModel("Models/Woodstock.obj");
	alaDerechaWoodstock.LoadModel("Models/alaDerechaWoodstock.obj");
	alaIzquierdaWoodstock.LoadModel("Models/alaIzquierdaWoodstock.obj");
	snoopy.LoadModel("Models/snoopy.obj");
	snoopyHouse.LoadModel("Models/snoopyHouse.obj");
	snoopySanta.LoadModel("Models/snoopySanta.obj");
	banca.LoadModel("Models/banca.obj");
	basura.LoadModel("Models/basura.obj");
	lampara.LoadModel("Models/lampara.obj");
	charlieCarpa.LoadModel("Models/carpaCharlie.obj");
	mesaDados.LoadModel("Models/mesaDados.obj");
	charlieBrown.LoadModel("Models/charlieBrown.obj");
	dado.LoadModel("Models/dado.obj");
	arbol.LoadModel("Models/arbol.obj");
	pino.LoadModel("Models/pino.obj");
	standDardos.LoadModel("Models/standDardos.obj");
	pikachu.LoadModel("Models/pikachu.obj");
	jigglypuff.LoadModel("Models/jigglypuff.obj");
	squirtle.LoadModel("Models/squirtle.obj");
	charmander.LoadModel("Models/charmander.obj");
	pichu.LoadModel("Models/pichu.obj");
	ash.LoadModel("Models/ash.obj");
	brock.LoadModel("Models/brock.obj");
	carpaPokemon.LoadModel("Models/carpaPokemon.obj");
	puestoPan.LoadModel("Models/puestoPan.obj");
	puestoRefrescos.LoadModel("Models/puestoRefrescos.obj");
	globosPokemon.LoadModel("Models/globosPokemon.obj");
	dardo.LoadModel("Models/dardo.obj");
	mesa.LoadModel("Models/mesa.obj");

	minosModelsList.push_back(&minosUpperRightArm);
	minosModelsList.push_back(&minosUpperLeftArm);
	minosModelsList.push_back(&minosRightThigh);
	minosModelsList.push_back(&minosRightLeg);
	minosModelsList.push_back(&minosLowerRightHand);
	minosModelsList.push_back(&minosLowerLeftArm);
	minosModelsList.push_back(&minosLeftThigh);
	minosModelsList.push_back(&minosLeftLeg);
	minosModelsList.push_back(&minosHead);
	minosModelsList.push_back(&minosBody);

	minosVeinsModelsList.push_back(&minosVeinsUpperRightArm);
	minosVeinsModelsList.push_back(&minosVeinsUpperLeftArm);
	minosVeinsModelsList.push_back(&minosVeinsRightThigh);
	minosVeinsModelsList.push_back(&minosVeinsRightLeg);
	minosVeinsModelsList.push_back(&minosVeinsLowerRightArm);
	minosVeinsModelsList.push_back(&minosVeinsLowerLeftArm);
	minosVeinsModelsList.push_back(&minosVeinsLeftThigh);
	minosVeinsModelsList.push_back(&minosVeinsLeftLeg);
	minosVeinsModelsList.push_back(&minosVeinsBody);
	minosVeinsModelsList.push_back(&corazonMinos);


	//archivos zim
	Puestogloboszim_M = Model();
	Puestogloboszim_M.LoadModel("Models/carritodeglobosAdrian.obj");
	Puestopizzazim_M = Model();
	Puestopizzazim_M.LoadModel("Models/puestodepizzaAdrian.obj");
	Puestohachazim_M = Model();
	Puestohachazim_M.LoadModel("Models/tiroconhacha.obj");
	Puestotoposzim_M = Model();
	Puestotoposzim_M.LoadModel("Models/pegaletopo.obj");
	NPCGloboszim_M = Model();
	NPCGloboszim_M.LoadModel("Models/NPCglobos.obj");
	NPCToposzim_M = Model();
	NPCToposzim_M.LoadModel("Models/NPCtopos.obj");
	NPCMartillotoposzim_M = Model();
	NPCMartillotoposzim_M.LoadModel("Models/NPCtoposMartillo.obj");
	NPCPizzazim_M = Model();
	NPCPizzazim_M.LoadModel("Models/NPCpizza.obj");
	NPChachazim_M = Model();
	NPChachazim_M.LoadModel("Models/NPChacha.obj");
	CerditoOjosNorm_M = Model();
	CerditoOjosNorm_M.LoadModel("Models/cerditoOjosNorm.obj");
	CerditoOjosX_M = Model();
	CerditoOjosX_M.LoadModel("Models/cerditoOjosX.obj");
	NPCBrazo1pizza_M = Model();
	NPCBrazo1pizza_M.LoadModel("Models/NPCbrazo1pizza.obj");
	NPCOjosabiertos_M = Model();
	NPCOjosabiertos_M.LoadModel("Models/NPCojosabiertospizza.obj");
	NPCOjoscerrados_M = Model();
	NPCOjoscerrados_M.LoadModel("Models/NPCojoscerradospizza.obj");
	NPCDibbrazo_M = Model();
	NPCDibbrazo_M.LoadModel("Models/dibbrazo.obj");
	NPChacha_M = Model();
	NPChacha_M.LoadModel("Models/NPChachagira.obj");
	NPCbrazoglobos_M = Model();
	NPCbrazoglobos_M.LoadModel("Models/NPCbrazoglobos.obj");
	CasaZim_M = Model();
	CasaZim_M.LoadModel("Models/casazimhachas.obj");
	Hachacasazim_M = Model();
	Hachacasazim_M.LoadModel("Models/hachacasazim1.obj");
	


	bowlingModelsList.push_back(&idol);
	bowlingModelsList.push_back(&maurice);
	bowlingModelsList.push_back(&terminal);
	bowlingModelsList.push_back(&mesaBoliche);
	bowlingModelsList.push_back(&chandelier);
	bowlingModelsList.push_back(&bowlingRailing);
	bowlingModelsList.push_back(&bowlingLaneFloor);
	bowlingModelsList.push_back(&carpet);
	bowlingModelsList.push_back(&cerberusStatue);
	bowlingModelsList.push_back(&bowlingChair);

	battingModelsList.push_back(&cerberus);
	battingModelsList.push_back(&cerberusOrb);
	battingModelsList.push_back(&feedbackerUpper);
	battingModelsList.push_back(&terminal);
	battingModelsList.push_back(&rejaBateo);
	battingModelsList.push_back(&v1Ultrakill);
	battingModelsList.push_back(&feedbackerLower);

	diceModelsList.push_back(&charlieCarpa);
	diceModelsList.push_back(&mesaDados);
	diceModelsList.push_back(&dado);
	diceModelsList.push_back(&charlieBrown);

	dartsModelsList.push_back(&carpaPokemon);
	dartsModelsList.push_back(&standDardos);
	dartsModelsList.push_back(&pikachu);
	dartsModelsList.push_back(&jigglypuff);
	dartsModelsList.push_back(&squirtle);
	dartsModelsList.push_back(&charmander);
	dartsModelsList.push_back(&dardo);
	dartsModelsList.push_back(&mesa);
	dartsModelsList.push_back(&ash);

	breadModelsList.push_back(&puestoPan);
	breadModelsList.push_back(&snoopy);

	sodaModelsList.push_back(&puestoRefrescos);
	sodaModelsList.push_back(&snoopy);

	pokemonBalloonsModelsList.push_back(&globosPokemon);
	pokemonBalloonsModelsList.push_back(&brock);

	woodstockModelsList.push_back(&snoopyHouse);
	woodstockModelsList.push_back(&snoopy);
	woodstockModelsList.push_back(&woodstock);
	woodstockModelsList.push_back(&alaDerechaWoodstock);
	woodstockModelsList.push_back(&alaIzquierdaWoodstock);


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

	pointLights[0] = PointLight(0.0f, .7f, 0.7f,
		0.0f, 1.0f,
		-0.0f, 2.f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	pointLights[1] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, 45.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[2] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, 15.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[3] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, -15.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[4] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, -45.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[5] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, 0.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[6] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -40.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[7] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -75.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[8] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -100.0f,
		0.5f, 0.2f, 0.0f);
	pointLightCount++;

	pointLights[9] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -155.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[10] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -210.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[11] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -245.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[12] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -285.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[13] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -335.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;

	pointLights[14] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -375.0f,
		0.5f, 0.15f, 0.0f);
	pointLightCount++;


	unsigned int contadorLucesPuntuales = 0;

	lucesPuntuales[0] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, 45.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[1] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, 15.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[2] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, -15.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[3] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		0.0f, -113.0f, -45.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[4] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, 0.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[5] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -40.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[6] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -75.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[7] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -100.0f,
		0.5f, 0.2f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[8] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -155.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[9] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -210.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[10] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -245.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[11] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -285.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[12] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		8.0f, 8.0f, -335.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;

	lucesPuntuales[13] = PointLight(1.0f, 1.0f, 1.0f,
		0.5f, 0.5f,
		-8.0f, 8.0f, -375.0f,
		0.5f, 0.15f, 0.0f);
	contadorLucesPuntuales++;
	

	//Spotlights
	unsigned int spotLightCount = 0;

	
	for (int i = 0;i < 7;i++) bowlingAnimation[i] = 0.0f;
	for (int i = 0;i < 4;i++) battingAnimation[i] = 0.0f;
	for (int i = 0;i < 4;i++) parryAnimation[i] = 0.0f;

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0, signPosition = 0;
	GLuint uniformColor = 0;


	GLfloat anguloVaria = 0.0f;
	//Variables del sol
	GLfloat sunIntensity = 0.2f;
	GLfloat sunIntensityMax = 0.6f;
	GLfloat sunIntensityMin = 0.1f;
	GLfloat sunIncrement = 0.0001f;
	GLfloat sunX = 0.3f;
	GLfloat sunY = -1.0f;
	GLfloat signFrameTime = 0.0;
	GLboolean isMorning = true;
	GLint activeSkybox = -1;
	GLfloat now = 0.0f;
	GLboolean bowlingActive = false;
	GLboolean battingReverse = false;
	GLboolean parryReverse = false;
	glm::vec3 cameraPos;
	glm::vec3 cameraDir;
	glm::vec2 toffsetSign = glm::vec2(0.0f, 0.0f);



	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	int activeCameraIndex = 0;
	Camera* activeCamera = &camera;
	float birdsEyeViewZPos = 0.0f;
	GLboolean birdsEyeViewReverse = false;

	messageCoordinates.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	messageCoordinates.push_back(glm::vec2(0.6666f, -0.3333f)); //P
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.3333f)); //R
	messageCoordinates.push_back(glm::vec2(0.5555f, -0.3333f)); //O
	messageCoordinates.push_back(glm::vec2(0.6666f, -0.6666f)); //Y
	messageCoordinates.push_back(glm::vec2(0.4444f, 0.0f)); //E
	messageCoordinates.push_back(glm::vec2(0.2222f, 0.0f)); //C
	messageCoordinates.push_back(glm::vec2(0.1111f, -0.6666f)); //T
	messageCoordinates.push_back(glm::vec2(0.5555f, -0.3333f)); //O
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	messageCoordinates.push_back(glm::vec2(0.2222f, 0.0f)); //C
	messageCoordinates.push_back(glm::vec2(0.6666f, 0.0f)); //G
	messageCoordinates.push_back(glm::vec2(0.4444f, 0.0f)); //E
	messageCoordinates.push_back(glm::vec2(0.8888f, 0.0f)); //I
	messageCoordinates.push_back(glm::vec2(0.7777f, 0.0f)); //H
	messageCoordinates.push_back(glm::vec2(0.2222f, 0.0f)); //C
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.6666f)); //
	messageCoordinates.push_back(glm::vec2(0.5555f, 0.0f)); //F
	messageCoordinates.push_back(glm::vec2(0.4444f, 0.0f)); //E
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.3333f)); //R
	messageCoordinates.push_back(glm::vec2(0.8888f, 0.0f)); //I
	messageCoordinates.push_back(glm::vec2(0.0f, 0.0f)); //A
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.6666f)); // 
	messageCoordinates.push_back(glm::vec2(0.8888f, -0.6666f)); // 

	GLint messageCoordinatesArraySize = messageCoordinates.size() - 1;
	////*****************Loop mientras no se cierra la ventana**************************
	while (!mainWindow.getShouldClose())
	{

		now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Set Active Camera
		activeCameraIndex = mainWindow.getCameraIndex();
		activeCamera = cameraList[activeCameraIndex];

		//Birds Eye View Camera Panning
		if (activeCameraIndex == 1) {
			glm::vec3 activeCameraPosition = activeCamera->getCameraPosition();
			if (!birdsEyeViewReverse) birdsEyeViewZPos = activeCameraPosition.z - 0.5 * deltaTime;
			else birdsEyeViewZPos = activeCameraPosition.z + 0.5 * deltaTime;
			if (birdsEyeViewZPos < -430.0f && !birdsEyeViewReverse) birdsEyeViewReverse = !birdsEyeViewReverse;
			else if (birdsEyeViewZPos > 130.0f && birdsEyeViewReverse) birdsEyeViewReverse = !birdsEyeViewReverse;
			activeCamera->teleport(glm::vec3(activeCameraPosition.x, activeCameraPosition.y, birdsEyeViewZPos));
		}

		//Recibir eventos del usuario
		glfwPollEvents();
		activeCamera->keyControl(mainWindow.getsKeys(), deltaTime);
		activeCamera->mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		cameraPos = camera.getCameraPosition();
		cameraDir = camera.getCameraDirection();

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(activeCamera->calculateViewMatrix(), projection);
		
		shaderList[0].UseShader();

		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//informaci�n en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();
		
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(activeCamera->calculateViewMatrix()));
		glUniform3f(uniformEyePosition, activeCamera->getCameraPosition().x, activeCamera->getCameraPosition().y, activeCamera->getCameraPosition().z);

		//Main Light y skybox
		mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
			sunIntensity, sunIntensity,
			sunX, sunY, .0f);

		if (isMorning==true) {
			sunIntensity = sunIntensity + sunIncrement;
			sunX = sin(sunIntensity);
			sunY = -sunIntensity / sunIntensityMax;
			if (sunIntensity >= sunIntensityMax) isMorning = false;
		}
		else {
			sunIntensity = sunIntensity - sunIncrement;
			sunX = -sin(sunIntensity);
			sunY = -sunIntensity / sunIntensityMax;
			if (sunIntensity <= sunIntensityMin) isMorning = true;
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

		
		//informaci�n al shader de fuentes de iluminaci�n
		shaderList[0].SetDirectionalLight(&mainLight);

		if (mainWindow.getOrbLight()) {
			if (sunIntensity < 0.2)
				shaderList[0].SetPointLights(pointLights, pointLightCount);
			else if (sunIntensity < 0.27)
				shaderList[0].SetPointLights(pointLights, pointLightCount - 10);
			else
				shaderList[0].SetPointLights(pointLights, pointLightCount - 14);
		}
		else {
			if (sunIntensity < 0.2)
				shaderList[0].SetPointLights(lucesPuntuales, contadorLucesPuntuales);
			else if (sunIntensity < 0.27)
				shaderList[0].SetPointLights(lucesPuntuales, contadorLucesPuntuales - 10);
			else
				shaderList[0].SetPointLights(lucesPuntuales, contadorLucesPuntuales - 14);
		}

		shaderList[0].SetSpotLights(spotLights, spotLightCount);
		
		


		//Matrices
		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::mat4 modelauxCuerpo(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

		float angulo = atan2(cameraDir.x, cameraDir.z);

		float distanciaDetras = -7.0f;
		glm::vec3 posicionModelo = cameraPos - cameraDir * distanciaDetras;
		posicionModelo.y = cameraPos.y - 1.0f;

		if (mainWindow.getOrbLight()) printf("x: %f y: %f z: %f\n", posicionModelo.x, posicionModelo.y, posicionModelo.z);

		//********************* Pisos *******************
		//Piso
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -30.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -1.0f, -630.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));

		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//Calle
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -.9f, -30.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

		brickTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -.9f, -100.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));



		meshList[3]->RenderMesh();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(40.0f, -.9f, -20.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 5.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


		meshList[3]->RenderMesh();

		
		//**************************** Modelos ***************************
		// 
		// Elementos de ambiente 
		elementosAmbiente(model, uniformModel, banca, basura, lampara, arbol, pino);
    
		// Juego de Dados
		renderJuegoDados(model, uniformModel, diceModelsList, *meshList[4], pisoBoliche);
				
		// Juego de Dardos
		renderJuegoDardos(model, uniformModel, dartsModelsList, *meshList[4], pisoBoliche, posicionModelo.x, posicionModelo.z, mainWindow.getEPressed(), deltaTime);
		
		// Puesto de Pan
		renderPuestoPan(model, uniformModel, breadModelsList);

		// Puesto de Refrescos
		renderPuestoRefrescos(model, uniformModel, sodaModelsList);

		// Globos de Pokemon
		renderPuestoGlobosPokemon(model, uniformModel, pokemonBalloonsModelsList);

		// Woodstock
		renderWoodstock(model, uniformModel, woodstockModelsList, deltaTime);

		// Pichu
		renderPichu(model, uniformModel, pichu, deltaTime);

		// Snoopy Santa
		renderSnoopySanta(model, uniformModel, snoopySanta, deltaTime);

			
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

		
		
		//Boliche TP y Render
		if ((cameraPos.x > 87.82 && cameraPos.x < 110.13 && cameraPos.z < 101.43 && cameraPos.z > -109.71) && cameraPos.y == 6.0) {
			bowlingActive = true;
			camera.teleport(glm::vec3(-45.0f, -117.5f, 40.0f));
		}

		if ((cameraPos.x < -50.0f || cameraPos.x > 45.0f && cameraPos.z > 57.0f || cameraPos.z < -53.0f) && cameraPos.y < 0.0) {
			bowlingActive = false;
			camera.teleport(glm::vec3(0.0f, 6.0f, 0.0f));
		}

		if(bowlingActive) renderBoliche(model, uniformModel, bowlingModelsList, bowlingMeshList, bowlingTextureList, mainWindow.getEPressed(),posicionModelo, bowlingAnimation, deltaTime);

		renderBatting(model, uniformModel, battingModelsList, battingMeshList, battingTextureList, battingAnimation, deltaTime, mainWindow.getEPressed(), posicionModelo, &battingReverse, parryAnimation, &parryReverse);


		
		// PUESTO GLOBOS ------------------------------
		renderPuestoGlobosZim(model, uniformModel, Puestogloboszim_M);

		// base común del personaje y sus partes
		glm::mat4 modelauxGlobos = glm::mat4(1.0f);
		modelauxGlobos = glm::translate(modelauxGlobos, glm::vec3(15.0f, 0.0f, -370.0f)); // posición del NPC
		modelauxGlobos = glm::scale(modelauxGlobos, glm::vec3(1.5f, 1.5f, 1.5f));         // escala
		modelauxGlobos = glm::rotate(modelauxGlobos, glm::radians(0.0f), glm::vec3(0, 1, 0)); // rotación Y

		// cuerpo del NPC
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelauxGlobos));
		NPCGloboszim_M.RenderModel();

		// brazo jerárquico
		renderBrazoNPCGlobos(modelauxGlobos, uniformModel, NPCbrazoglobos_M, now);



		//PUESTO HACHA.............................................
		//puesto hacha zim
		renderTiroHachaZim(model, uniformModel, Puestohachazim_M);

		glm::mat4 modelauxzim = glm::mat4(1.0f);
		modelauxzim = glm::translate(modelauxzim, glm::vec3(30.5f, 0.0f, -198.0f));
		modelauxzim = glm::rotate(modelauxzim, glm::radians(-90.0f), glm::vec3(0, 1, 0));
		modelauxzim = glm::scale(modelauxzim, glm::vec3(2.5f, 2.5f, 2.5f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelauxzim));
		NPChachazim_M.RenderModel(); // cuerpo Dib
		float factorLanzamiento = (sin(now * 2.0f) + 1.0f) / 2.0f;
		//NPC brazo
		renderNPCBrazoDib(modelauxzim, uniformModel, NPCDibbrazo_M, factorLanzamiento);
		//NPC hacha
		renderHachaLanzada(modelauxzim, uniformModel, factorLanzamiento);
		//Casa zim
		renderCasaHachaZim(model, uniformModel, CasaZim_M, Hachacasazim_M, now);



		//........................................................
	 


		//puesto topo zim
		renderPuestoToposZim(model, uniformModel, Puestotoposzim_M);
		//NPC puesto topo zim
		renderNPCPuestoToposZim(model, uniformModel, NPCToposzim_M);

		//NPC puesto topo Martillo (animado)
		renderNPCMartilloPuestoToposZim(model, uniformModel, NPCMartillotoposzim_M);
		
		//NPC puesto de pizza
		renderNPCPuestoPizzaZim(model, uniformModel, NPCPizzazim_M);
		//NPC ojos puesto de pizza (animado)
		renderNPCOjosPizzaZim(model, uniformModel, now); 

		//NPC brazo1 puesto de pizza(animado)
		renderNPCBrazo1PuestoPizzaZim(model, uniformModel, NPCBrazo1pizza_M, now);





		//************************************Transparentes **********************************
		

		

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		//***************** Arco ********************
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-3.0f, -.0f, 130.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.8f, 1.8f, 1.8f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ultrakillArch.RenderModel();

		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 4.6f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ultrakillDoor.RenderModel();


		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -7.5f));
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ultrakillDoor.RenderModel();


		if (signFrameTime >= 40.0f) {
			signPosition += 1;
			signFrameTime = 0.0f;
			if (signPosition == messageCoordinatesArraySize) signPosition = 0;
		}
		signFrameTime += deltaTime;

		toffsetSign = messageCoordinates[signPosition];


		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.7f, 12.0f, -0.5f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, .0f, 1.0f));
		model = glm::scale(model, glm::vec3(1.6f, 1.0f, 3.f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffsetSign));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		ultrakillFont.UseTexture();
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[4]->RenderMesh();


		toffsetSign = messageCoordinates[signPosition + 1];
		if (signPosition + 1 > messageCoordinatesArraySize) toffsetSign = messageCoordinates[messageCoordinatesArraySize];
		model = glm::translate(model, glm::vec3(.7f, .0f, .0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffsetSign));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();


		if (signPosition + 2 > messageCoordinatesArraySize) toffsetSign = messageCoordinates[messageCoordinatesArraySize];
		else toffsetSign = messageCoordinates[signPosition + 2];
		model = glm::translate(model, glm::vec3(.7f, .0f, .0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffsetSign));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();


		if (signPosition + 3 > messageCoordinatesArraySize) toffsetSign = messageCoordinates[messageCoordinatesArraySize];
		else toffsetSign = messageCoordinates[signPosition + 3];
		model = glm::translate(model, glm::vec3(.7f, .0f, .0f));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffsetSign));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[4]->RenderMesh();
		toffsetSign = glm::vec2(0.0f, 0.0f);
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffsetSign));
		//puesto de pizza
		renderPuestoPizzaZim(model, uniformModel, Puestopizzazim_M);

		//Placeholder Antojitos
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(25.0f, -1.0f, -130.f));
		modelaux = model;
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
		model = glm::scale(model, glm::vec3(3.2f, 3.2f, 3.2f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		v2Ultrakill.RenderModel();

		//Placeholder antojitos
		model = modelaux;
		model = glm::translate(model, glm::vec3(.0f, 0.0f, 2.0));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
		model = glm::scale(model, glm::vec3(4.f, 4.f, 4.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ultraEsquites.RenderModel();

		//Ultrakill esquites
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-30.0f, -1.0f, -300.f));
		modelaux = model;
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));
		model = glm::scale(model, glm::vec3(3.2f, 3.2f, 3.2f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		v2Ultrakill.RenderModel();
		

		//
		model = modelaux;
		model = glm::translate(model, glm::vec3(.0f, 0.0f, -2.0));
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));
		model = glm::scale(model, glm::vec3(4.f, 4.f, 4.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ultraEsquites.RenderModel();
		

		//Fountain
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 2.0f, -175.f));
		modelaux = model;
		model = glm::scale(model, glm::vec3(0.7f, 0.7f, 0.7f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		ultrakillFountain.RenderModel();

		model = glm::translate(model, glm::vec3(3.0f, 3.0f, 0.f));
		model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cerberusStatue.RenderModel();



		//Minos Prime Avatar Animado
		if(mainWindow.getOrbLight())
			pointLights[0].MoveLight(glm::vec3(posicionModelo.x, posicionModelo.y + .5f, posicionModelo.z));
		renderMinosVenas(model, modelaux, modelauxCuerpo, uniformModel, minosVeinsModelsList, posicionModelo, angulo, camera.anguloVaria);
		renderMinos(model, modelaux, modelauxCuerpo, uniformModel, minosModelsList, posicionModelo, angulo, camera.anguloVaria);
		

		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		/* Static model
		// Venas
		model = glm::mat4(1.0f);
		model = glm::translate(model, posicionModelo);
		model = glm::scale(model, glm::vec3(4.0f, 4.0f, 4.0f));

		model = glm::rotate(model, angulo, glm::vec3(0.0f, 1.0f, 0.0f));
		modelaux = model;
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
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

    */
		//puesto de pizza zim
		

		
		glDisable(GL_BLEND);
		
		

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
