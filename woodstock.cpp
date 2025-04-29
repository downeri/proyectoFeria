#include "woodstock.h"

float movimientoWoodstock = 0.0f;

void renderWoodstock(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, float deltaTime) {

	glm::vec3 posicion = glm::vec3(0.0f, -1.0f, -30.0f);
	glm::mat4 modelaux(1.0);

	movimientoWoodstock += 1.0f * deltaTime;
	if (movimientoWoodstock >= 360.0f)
		movimientoWoodstock = 0.0f;

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x, posicion.y, posicion.z));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(15.0f, 15.0f, 15.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[0]->RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x, posicion.y + 8.75f, posicion.z + 2.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[1]->RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x, posicion.y + 10.0f, posicion.z + sin(glm::radians(movimientoWoodstock)) * 5.0f));
	model = glm::translate(model, glm::vec3(cos(glm::radians(movimientoWoodstock)) * 5.0f, 0.0f, 0.0f));
	model = glm::translate(model, glm::vec3(0.0f, sin(glm::radians(movimientoWoodstock * 5.0f)), 0.0f));
	model = glm::rotate(model, glm::radians(-movimientoWoodstock), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[2]->RenderModel();

	modelaux = model;
	model = glm::translate(model, glm::vec3(-0.1f, 0.0f, 0.0));
	model = glm::rotate(model, sin(glm::radians(movimientoWoodstock * 5.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[3]->RenderModel();
	model = modelaux;

	modelaux = model;
	model = glm::translate(model, glm::vec3(0.1f, 0.0f, 0.0));
	model = glm::rotate(model, -sin(glm::radians(movimientoWoodstock * 5.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[4]->RenderModel();
	model = modelaux;
}