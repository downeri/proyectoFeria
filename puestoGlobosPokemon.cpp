#include "puestoGlobosPokemon.h"

void renderPuestoGlobosPokemon(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(20.0f, -1.0f, -380.0f));
	model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[0]->RenderModel();
}