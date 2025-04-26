#include "PuestoPizzaZim.h"

void renderPuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& puestoPizza) {
    model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(6.0f, 0.0f, -14.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    puestoPizza.RenderModel();
}
