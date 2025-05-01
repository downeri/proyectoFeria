#pragma once

#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

void renderPuestoGlobosZim(glm::mat4 model, GLuint uniformModel, Model& puestoGlobos);

void renderNPCGlobosZim(glm::mat4 model, GLuint uniformModel, Model& npcGlobos);

void renderBrazoNPCGlobos(glm::mat4 modelCuerpo, GLuint uniformModel, Model& brazo, float factorLanzamiento);
