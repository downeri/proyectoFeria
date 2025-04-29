#include "PuestoGlobosZim.h"

void renderPuestoGlobosZim(glm::mat4 model, GLuint uniformModel, Model& puestoGlobos) {
    model = glm::mat4(1.0f); 
    model = glm::translate(model, glm::vec3(13.0f, 0.0f, -370.0f)); //x, y, z
    model = glm::scale(model, glm::vec3(2.5f, 2.5f, 2.5f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    puestoGlobos.RenderModel();
}

void renderNPCGlobosZim(glm::mat4 model, GLuint uniformModel, Model& npcGlobos) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(15.0f, 0.0f, -370.0f));//x, y, z
    model = glm::scale(model, glm::vec3(1.5f, 1.5f, 1.5f));
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 1, 0));
  
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    npcGlobos.RenderModel();
}
