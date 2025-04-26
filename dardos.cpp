#include "dardos.h"

void renderJuegoDardos(glm::mat4 model, GLuint uniformModel, std::vector<Model> listaModelos) {
	glm::vec3 posicion = glm::vec3(-20.0f, -1.0f, -250.0f);

	model = glm::mat4(1.0);
	model = glm::translate(model, posicion);
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 4.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[0].RenderModel();

	renderStandDardos(model, uniformModel, listaModelos[1], posicion, glm::vec3(-7.0f, 0.0f, -15.0f));
	renderStandDardos(model, uniformModel, listaModelos[1], posicion, glm::vec3(-7.0f, 0.0f, -5.0f));
	renderStandDardos(model, uniformModel, listaModelos[1], posicion, glm::vec3(-7.0f, 0.0f, 5.0f));
	renderStandDardos(model, uniformModel, listaModelos[1], posicion, glm::vec3(-7.0f, 0.0f, 15.0f));

	renderPikachus(model, uniformModel, listaModelos[2], posicion, glm::vec3(-5.0f, 8.0f, -22.5f));
	renderPikachus(model, uniformModel, listaModelos[2], posicion, glm::vec3(-5.0f, 4.0f, -22.5f));

	renderJigglypuffs(model, uniformModel, listaModelos[3], posicion, glm::vec3(-5.0f, 6.0f, -22.5f));
	renderJigglypuffs(model, uniformModel, listaModelos[3], posicion, glm::vec3(-5.0f, 2.0f, -22.5f));

	renderSquirtles(model, uniformModel, listaModelos[4], posicion, glm::vec3(5.0f, 2.0f, 22.0f));
	renderSquirtles(model, uniformModel, listaModelos[4], posicion, glm::vec3(5.0f, 6.0f, 22.0f));

	renderCharmanders(model, uniformModel, listaModelos[5], posicion, glm::vec3(5.0f, 4.0f, 22.0f));
	renderCharmanders(model, uniformModel, listaModelos[5], posicion, glm::vec3(5.0f, 8.0f, 22.0f));
}
void renderStandDardos(glm::mat4 model, GLuint uniformModel, Model standDardos, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x + translate.x, position.y + translate.y, position.z + translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	standDardos.RenderModel();
}
void renderPikachus(glm::mat4 model, GLuint uniformModel, Model pikachu, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x + translate.x, position.y + translate.y, position.z + translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pikachu.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pikachu.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pikachu.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pikachu.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pikachu.RenderModel();
}
void renderJigglypuffs(glm::mat4 model, GLuint uniformModel, Model jigglypuff, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x + translate.x, position.y + translate.y, position.z + translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jigglypuff.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jigglypuff.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jigglypuff.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jigglypuff.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	jigglypuff.RenderModel();
}
void renderSquirtles(glm::mat4 model, GLuint uniformModel, Model squirtle, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x + translate.x, position.y + translate.y, position.z + translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	squirtle.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	squirtle.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	squirtle.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	squirtle.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	squirtle.RenderModel();
}
void renderCharmanders(glm::mat4 model, GLuint uniformModel, Model charmander, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x + translate.x, position.y + translate.y, position.z + translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	charmander.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	charmander.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	charmander.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	charmander.RenderModel();
	model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	charmander.RenderModel();
}