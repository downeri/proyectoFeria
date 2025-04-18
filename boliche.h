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

void renderBoliche(glm::mat4 model, GLuint uniformModel, std::vector<Model> listaModelos);
void renderPines(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb, glm::vec3 posInicial);
void renderTerminal(glm::mat4 model, GLuint uniformModel, Model& terminal, glm::vec3 position);
void renderMauriceBowling(glm::mat4 model, GLuint uniformModel, Model & maurice);
void renderTable(glm::mat4 model, GLuint uniformModel, Model& table, glm::vec3 position);