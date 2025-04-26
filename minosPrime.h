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

void renderMinos(glm::mat4 model, glm::mat4 modelaux, glm::mat4 modelauxCuerpo, GLuint uniformModel, std::vector<Model*> listaModelosMinos, glm::vec3 pos, GLfloat angulo, GLfloat anguloAnimacion);
void renderMinosVenas(glm::mat4 model, glm::mat4 modelaux, glm::mat4 modelauxCuerpo, GLuint uniformModel, std::vector<Model*> listaModelosMinosVenas, glm::vec3 pos, GLfloat angulo, GLfloat anguloAnimacion);
