#include "ambiente.h"

void elementosAmbiente(glm::mat4 model, GLuint uniformModel, Model& banca, Model& basura, Model& lampara, Model& arbol, Model& pino) {

	// Bancas
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-8.0f, -1.0f, -30.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();
	model = glm::translate(model, glm::vec3(20.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();
	model = glm::translate(model, glm::vec3(67.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();
	model = glm::translate(model, glm::vec3(57.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(8.0f, -1.0f, -50.0f));
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();
	model = glm::translate(model, glm::vec3(-30.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();
	model = glm::translate(model, glm::vec3(-47.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	banca.RenderModel();

	// Botes de basura
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-8.0f, -1.0f, -25.0f));
	model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();
	model = glm::translate(model, glm::vec3(53.3f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();
	model = glm::translate(model, glm::vec3(178.6f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();
	model = glm::translate(model, glm::vec3(152.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(8.0f, -1.0f, -45.0f));
	model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();
	model = glm::translate(model, glm::vec3(-80.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();
	model = glm::translate(model, glm::vec3(-125.3f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	basura.RenderModel();

	// Lamparas
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-8.0f, -1.0f, -40.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(60.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(110.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(75.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(90.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(8.0f, -1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(-75.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(-80.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(-90.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();
	model = glm::translate(model, glm::vec3(-90.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lampara.RenderModel();

	// Árboles
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-15.0f, -1.0f, -30.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	arbol.RenderModel();
	model = glm::translate(model, glm::vec3(60.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pino.RenderModel();
	model = glm::translate(model, glm::vec3(120.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	arbol.RenderModel();
	model = glm::translate(model, glm::vec3(150.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pino.RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(15.0f, -1.0f, -50.0f));
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pino.RenderModel();
	model = glm::translate(model, glm::vec3(-60.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	arbol.RenderModel();
	model = glm::translate(model, glm::vec3(-120.0f, 0.0f, -30.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pino.RenderModel();
	/*model = glm::translate(model, glm::vec3(-60.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	arbol.RenderModel();*/
}