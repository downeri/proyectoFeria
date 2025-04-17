#include "test.h"


void testFunc(GLuint uniformModel, Model& cerberusOrb) {
	glm::mat4 model(1.0);
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 5.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.005f, 0.005f, 0.005f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cerberusOrb.RenderModel();
}