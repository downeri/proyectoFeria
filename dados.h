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

#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Mesh.h"
#include "Camera.h"
#include "Window.h"

#include "Material.h"

void renderJuegoDados(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, Mesh& piso, Texture& pisoTextura, float posicionX, float posicionZ, GLboolean getEPressed, float deltaTime);
void renderMesaDados(glm::mat4 model, GLuint uniformModel, Model &mesaDados, glm::vec3 position, glm::vec3 translate);
void renderDados(glm::mat4 model, GLuint uniformModel, Model& dados, glm::vec3 position, glm::vec3 translate, int mesa, float deltaTime);