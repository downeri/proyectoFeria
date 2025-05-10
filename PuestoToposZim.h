#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Model.h"
#include "Texture.h"      

extern float  anguloMartillo;
extern const float angMin;

extern Texture ojosNormales;
extern Texture ojosGolpeado;
extern Model CerditoOjosNorm_M;   
extern Model CerditoOjosX_M;     



void renderPuestoToposZim(glm::mat4 model, GLuint uniformModel, Model& puestoTopos);


void renderNPCPuestoToposZim(glm::mat4 model, GLuint uniformModel, Model& npcToposCuerpo);

void renderNPCMartilloPuestoToposZim(glm::mat4 model, GLuint uniformModel, Model& npcMartilloTopos);



