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

void renderBattingBuilding(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, std::vector<Mesh*> bowlingMeshList, std::vector<Texture*> listaTexturas);
void renderFeedbacker(glm::mat4 model, GLuint uniformModel, Model& feedbacker);
void renderOrbBall(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb);
void renderCerberusPitcher(glm::mat4 model, GLuint uniformModel, Model& cerberus);
