#include "pichu.h"

float movimientoPichu = 0.0f;
float saltoPichu = 0.0f;
float distanciaPichu = 10.0f;
float offsetPichu = 0.1f;
bool idaPichu = true;

void renderPichu(glm::mat4 model, GLuint uniformModel, Model& pichu, float deltaTime) {
	if (movimientoPichu < -distanciaPichu)
		movimientoPichu = -distanciaPichu;
	if (movimientoPichu > distanciaPichu)
		movimientoPichu = distanciaPichu;

	saltoPichu += 1.0f * deltaTime;
	if (saltoPichu >= 360.0f)
		saltoPichu = 0.0f;

	if (movimientoPichu > -distanciaPichu && idaPichu == true) {
		movimientoPichu -= offsetPichu * deltaTime;
	}
	else if (movimientoPichu <= -distanciaPichu) {
		movimientoPichu += offsetPichu * deltaTime;
		idaPichu = false;
	}
	else if (movimientoPichu < distanciaPichu && idaPichu == false) {
		movimientoPichu += offsetPichu * deltaTime;
	}
	else {
		movimientoPichu -= offsetPichu * deltaTime;
		idaPichu = true;
	}

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(movimientoPichu, -1.1f, -20.0f));
	model = glm::translate(model, glm::vec3(0.0f, abs(sin(glm::radians(saltoPichu * 2.5f)) * 5.0f), 0.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	if (idaPichu == false)
		model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(0.75f, 0.75f, 0.75f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pichu.RenderModel();
}