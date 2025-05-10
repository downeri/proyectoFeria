#include "GIRZIM.h"
#include <glew.h>
#include <glfw3.h>
#include "Model.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

void renderGirZim(glm::mat4 model, GLuint uniformModel,
    Model& tronco_M, Model& cabeza_M,
    Model& brazo1_M, Model& brazo2_M,
    Model& pierna1_M, Model& pierna2_M,
    float now) {


    // Base del personaje (tronco)
    glm::mat4 troncoModel = glm::translate(model, glm::vec3(0.0f, 0.5f, 0.0f));
    troncoModel = glm::rotate(troncoModel, glm::radians(-90.0f), glm::vec3(0, 1, 0)); // rotación Y
    troncoModel = glm::scale(troncoModel, glm::vec3(1.0f, 1.0f, 1.0f));             // escala uniforme
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(troncoModel));
    tronco_M.RenderModel();

    // Cabeza
    glm::mat4 cabezaModel = troncoModel; // se hereda del tronco
    cabezaModel = glm::translate(cabezaModel, glm::vec3(0.0f, 0.1f, 0.0f)); // posicionar
    cabezaModel = glm::rotate(cabezaModel, glm::radians(360.0f * sin(now)), glm::vec3(0.0f, 1.0f, 0.0f)); // gira continuamente sobre eje Y
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(cabezaModel));
    cabeza_M.RenderModel();

    // Brazo derecho
    glm::mat4 brazo1Model = troncoModel;

    brazo1Model = glm::translate(brazo1Model, glm::vec3(0.025f, 0.05f, 0.05f));//z, y, x
    brazo1Model = glm::rotate(brazo1Model, glm::radians(30.0f * sin(now * 3.0f)), glm::vec3(1, 0, 0));
    brazo1Model = glm::scale(brazo1Model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(brazo1Model));
    brazo1_M.RenderModel();

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(brazo1Model));
    brazo1_M.RenderModel();

    // Brazo izquierdo
    glm::mat4 brazo2Model = glm::translate(troncoModel, glm::vec3(0.0f, 0.05f, -0.05f));
    brazo2Model = glm::rotate(brazo2Model, glm::radians(0.0f), glm::vec3(1, 0, 0));
    brazo2Model = glm::scale(brazo2Model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(brazo2Model));
    brazo2_M.RenderModel();

    // Pierna derecha
    glm::mat4 pierna1Model = glm::translate(troncoModel, glm::vec3(0.0f, -0.07f, 0.05f));
    pierna1Model = glm::rotate(pierna1Model, glm::radians(0.0f), glm::vec3(1, 0, 0));
    pierna1Model = glm::scale(pierna1Model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(pierna1Model));
    pierna1_M.RenderModel();

    // Pierna izquierda
    glm::mat4 pierna2Model = glm::translate(troncoModel, glm::vec3(0.0f, -0.07f, -0.05f));
    pierna2Model = glm::rotate(pierna2Model, glm::radians(0.0f), glm::vec3(1, 0, 0));
    pierna2Model = glm::scale(pierna2Model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(pierna2Model));
    pierna2_M.RenderModel();
}
