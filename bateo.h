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

#include "Mesh.h"

#include "Texture.h"
#include "Sphere.h"
#include"Model.h"

void renderBatting(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, std::vector<Mesh*> MeshList, std::vector<Texture*> listaTexturas);
void renderBattingBuilding(glm::mat4 model, GLuint uniformModel, std::vector<Mesh*> MeshList, std::vector<Texture*> listaTexturas, glm::vec3 position);
void renderFeedbacker(glm::mat4 model, GLuint uniformModel, Model& feedbacker);
void renderOrbBall(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb, glm::vec3 position);
void renderLava(glm::mat4 model, GLuint uniformModel, Mesh& lavaFloor, Texture& lavaTexture, glm::vec3 position);
void renderCerberusPitcher(glm::mat4 model, GLuint uniformModel, Model& cerberus, glm::vec3 position);
void renderOrbBall(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb, glm::vec3 position);
void renderReja(glm::mat4 model, GLuint uniformModel, Model& reja, glm::vec3 position);
void renderV1(glm::mat4 model, GLuint uniformModel, Model& v1Ultrakill, glm::vec3 position);