#include "dados.h"

void renderJuegoDados(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, Mesh& piso, Texture& pisoTextura) {
	glm::vec3 posicion = glm::vec3(-20.0f, -1.0f, -300.0f);

	model = glm::mat4(1.0);
	model = glm::translate(model, posicion);
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 4.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[0]->RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x - 6.0f, posicion.y, posicion.z));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[3]->RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x, posicion.y + 0.2f, posicion.z));
	model = glm::scale(model, glm::vec3(0.9f, 1.0f, 2.4f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pisoTextura.UseTexture();
	piso.RenderMesh();

	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, -15.0f));
	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, -5.0f));
	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, 5.0f));
	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, 15.0f));

	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.5f, -15.0f));
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.5f, -5.0f));
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.5f, 5.0f));
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.5f, 15.0f));

}

void renderMesaDados(glm::mat4 model, GLuint uniformModel, Model &mesaDados, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x+translate.x, position.y+translate.y, position.z+translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mesaDados.RenderModel();
}

void renderDados(glm::mat4 model, GLuint uniformModel, Model& dados, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x + translate.x + 0.5, position.y + translate.y, position.z + translate.z -0.5));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dados.RenderModel();
	model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	dados.RenderModel();
}