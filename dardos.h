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

void renderJuegoDardos(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, Mesh& piso, Texture& pisoTextura, float posicionX, float posicionZ, GLboolean getEPressed, float deltaTime);
void renderStandDardos(glm::mat4 model, GLuint uniformModel, Model &standDardos, glm::vec3 position, glm::vec3 translate);
void renderDardo(glm::mat4 model, GLuint uniformModel, Model& dardo, glm::vec3 position, glm::vec3 translate);
void renderPikachus(glm::mat4 model, GLuint uniformModel, Model &pikachu, glm::vec3 position, glm::vec3 translate);
void renderJigglypuffs(glm::mat4 model, GLuint uniformModel, Model &jigglypuff, glm::vec3 position, glm::vec3 translate);
void renderSquirtles(glm::mat4 model, GLuint uniformModel, Model &squirtle, glm::vec3 position, glm::vec3 translate);
void renderCharmanders(glm::mat4 model, GLuint uniformModel, Model &charmander, glm::vec3 position, glm::vec3 translate);
