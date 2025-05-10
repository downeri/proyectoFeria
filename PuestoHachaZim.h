#pragma once
#include "window.h"
#include "Camera.h"
#include "Model.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
extern  Model NPCDibbrazo_M;
extern bool lanzarHacha;

void renderTiroHachaZim(glm::mat4 model, GLuint uniformModel, Model& puestoHacha);

void renderNPCBrazoDib(glm::mat4 model, GLuint uniformModel, Model& brazoDib, float tiempo);

void renderHachaLanzada(glm::mat4 modelNPC, GLuint uniformModel, float tiempo);

void renderCasaHachaZim(glm::mat4& model, GLuint uniformModel, Model& casaZim, Model& hachaZim, float now);

void renderHachaVoladora(GLuint uniformModel, Model& hacha, float deltaTime, Camera& cam);


