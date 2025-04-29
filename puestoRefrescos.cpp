#include "puestoRefrescos.h"

void renderPuestoRefrescos(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos) {
	glm::vec3 posicion = glm::vec3(20.0f, -1.0f, -220.0f);
	model = glm::mat4(1.0);
	model = glm::translate(model, posicion);
	model = glm::scale(model, glm::vec3(3.5f, 3.5f, 3.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[0]->RenderModel();
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.1f));
	model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[1]->RenderModel();
}