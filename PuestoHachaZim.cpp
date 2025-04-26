#include "PuestoHachaZim.h"

void renderTiroHachaZim(glm::mat4 model, GLuint uniformModel, Model& puestoHacha) {
    model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(6.5f, 0.0f, -2.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    puestoHacha.RenderModel();
}
