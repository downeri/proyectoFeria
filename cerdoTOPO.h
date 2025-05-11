#pragma once
#include <glm.hpp>
#include <glew.h>

void renderCerdoTOPO(glm::vec3 posicionBase, GLuint uniformModel, float tiempoGlobal, float desfase);
void renderGrupoCerdos(glm::vec3 basePos, GLuint uniformModel, float now);
