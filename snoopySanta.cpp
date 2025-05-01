#include "snoopySanta.h"

float distanciSnoopySanta = 1000.0f;
float cruceSnoopySanta = distanciSnoopySanta;
float movimientoSnoopySanta = 0.0f;
float offsetSnoopySanta = 1.0f;

void renderSnoopySanta(glm::mat4 model, GLuint uniformModel, Model& snoopySanta, float deltaTime) {
	if (cruceSnoopySanta < -distanciSnoopySanta)
		cruceSnoopySanta = distanciSnoopySanta;

	cruceSnoopySanta -= offsetSnoopySanta * deltaTime;

	movimientoSnoopySanta += offsetSnoopySanta * deltaTime;
	if (movimientoSnoopySanta >= 360.0f)
		movimientoSnoopySanta = 0.0f;
	
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(cruceSnoopySanta, 200.0f, -300.0f));
	model = glm::translate(model, glm::vec3(0.0f, 25.0f * sin(glm::radians(movimientoSnoopySanta)), 0.0f));
	model = glm::rotate(model, glm::radians(25.0f * -cos(glm::radians(movimientoSnoopySanta))), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	snoopySanta.RenderModel();
}