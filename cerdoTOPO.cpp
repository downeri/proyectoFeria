#include "cerdoTOPO.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Model.h"



extern Model cerdoTOPO_M;

void renderCerdoTOPO(glm::vec3 posicionBase, GLuint uniformModel, float tiempoGlobal, float desfase)
{
    glm::mat4 model = glm::mat4(1.0f);

    float altura = sin((tiempoGlobal + desfase) * 3.0f) * 0.3f;

    model = glm::translate(model, posicionBase + glm::vec3(0.0f, altura, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    cerdoTOPO_M.RenderModel();
}
void renderGrupoCerdos(glm::vec3 basePos, GLuint uniformModel, float now) {
    renderCerdoTOPO(basePos + glm::vec3(0.0f, 0.0f, -0.02f), uniformModel, now, 0.0f);
    renderCerdoTOPO(basePos + glm::vec3(0.0f, 0.0f, -1.3f), uniformModel, now, 0.3f);
    renderCerdoTOPO(basePos + glm::vec3(0.0f, 0.0f, 1.1f), uniformModel, now, 0.6f);
    renderCerdoTOPO(basePos + glm::vec3(1.0f, 0.0f, 0.5f), uniformModel, now, 0.9f);
    renderCerdoTOPO(basePos + glm::vec3(1.0f, 0.0f, -0.65f), uniformModel, now, 0.9f);
}
