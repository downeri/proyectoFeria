#pragma once

#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
extern  Model NPCDibbrazo_M;


void renderTiroHachaZim(glm::mat4 model, GLuint uniformModel, Model& puestoHacha);

void renderNPCBrazoDib(glm::mat4 model, GLuint uniformModel, Model& brazoDib, float tiempo);

void renderHachaLanzada(glm::mat4 modelNPC, GLuint uniformModel, float tiempo);

void renderCasaHachaZim(glm::mat4& model, GLuint uniformModel, Model& casaZim, Model& hachaZim, float now);
