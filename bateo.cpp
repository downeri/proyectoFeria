#include "bateo.h"

void renderFeedbacker(glm::mat4 model, GLuint uniformModel, Model& feedbacker) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 13.0f, 0.0));
	model = glm::scale(model, glm::vec3(20.f, 20.f, 20.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	feedbacker.RenderModel();
}

void renderOrbBall(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cerberusOrb.RenderModel();
}

void renderCerberusPitcher(glm::mat4 model, GLuint uniformModel, Model& cerberus) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(4.0f, 1.5f, 0.f));
	model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cerberus.RenderModel();
}