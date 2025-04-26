#include "PuestoToposZim.h"

void renderPuestoToposZim(glm::mat4 model, GLuint uniformModel, Model& puestoTopos) {
    model = glm::mat4(1.0f);

    model = glm::scale(model, glm::vec3(0.8f, 0.8f, 0.8f));
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(15.0f, 0.0f, -17.0f)); //z,y,x

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    puestoTopos.RenderModel();
}
