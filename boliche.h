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

#include"Model.h"

void renderBoliche(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, std::vector<Mesh*> bowlingMeshList, std::vector<Texture*> listaTexturas, GLboolean ePressed, glm::vec3 modelPosition, GLfloat* bowlingAnimationLane, GLfloat deltaTime);

void renderBuilding(glm::mat4 model, GLuint uniformModel, std::vector<Mesh*> bowlingMeshList, std::vector<Texture*> listaTexturas, glm::vec3 position);
void renderPines(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb, glm::vec3 posInicial);
void renderPinesAnimation(glm::mat4 model, GLuint uniformModel, Model& idol, glm::vec3 posInicial, GLfloat rotation);
void renderTerminal(glm::mat4 model, GLuint uniformModel, Model& terminal, glm::vec3 position);
void renderMauriceBowling(glm::mat4 model, GLuint uniformModel, Model & maurice, glm::vec3 position, GLfloat rotation);
void renderTable(glm::mat4 model, GLuint uniformModel, Model& table, glm::vec3 position);
void renderChandelier(glm::mat4 model, GLuint uniformModel, Model& chandelier, glm::vec3 position);
void renderLaneFloor(glm::mat4 model, GLuint uniformModel, Model& laneFloor, glm::vec3 position);
void renderRailing(glm::mat4 model, GLuint uniformModel, Model& railing, glm::vec3 position);
void renderCarpet(glm::mat4 model, GLuint uniformModel, Model& carpet, glm::vec3 position);
void renderChair(glm::mat4 model, GLuint uniformModel, Model& chair, glm::vec3 position, GLfloat angle);
void renderCerberusStatue(glm::mat4 model, GLuint uniformModel, Model& cerberusStatue, glm::vec3 position);