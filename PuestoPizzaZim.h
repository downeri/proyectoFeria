#pragma once

#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


extern Model NPCOjosabiertos_M;
extern Model NPCOjoscerrados_M;

void renderPuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& puestoPizza);

void renderNPCPuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& npcPizza);

void renderNPCBrazo1PuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& NPCbrazo1Pizza, float tiempo);

void renderNPCOjosPizzaZim(glm::mat4 model, GLuint uniformModel, float tiempo);
