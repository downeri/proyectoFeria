#include "PuestoHachaZim.h"
#include <gtc/type_ptr.hpp>


void renderTiroHachaZim(glm::mat4 model, GLuint uniformModel, Model& puestoHacha) {
    float z = -150.0f;
    for (int i = 0;i < 5;i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(30.5f, 0.0f, z));
        model = glm::scale(model, glm::vec3(6.5f, 6.5f, 6.5f));
        model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));


        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        puestoHacha.RenderModel();
        z -= 10.0f;
    }
    
}


void renderNPCBrazoDib(glm::mat4 model, GLuint uniformModel, Model& brazoDib, float tiempo) {
    // Movimiento oscilatorio para simular lanzamiento
    float angulo = glm::radians(sin(tiempo * 2.0f) * 60.0f); // Oscila entre -60° y 60°

    // Trasladamos al punto de pivote del brazo (donde debería rotar)
    model = glm::translate(model, glm::vec3(-0.2f, 1.0f, 0.0f)); // Eje de rotación relativo al cuerpo

    // Rotación hacia arriba 
    model = glm::rotate(model, angulo, glm::vec3(0.0f, 0.0f, 1.0f)); 

    // Dibujar el modelo del brazo
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    brazoDib.RenderModel();
}




extern Model NPChacha_M;

void renderHachaLanzada(glm::mat4 modelNPC, GLuint uniformModel, float factor) {
    glm::mat4 model = modelNPC;

    // Posición relativa al cuerpo (mano)
    model = glm::translate(model, glm::vec3(-0.5f, 1.35f, 0.65f));

    // Movimiento vertical (lanza hacia arriba)
    float altura = factor * 2.0f;  // Ajusta la altura máxima
    model = glm::translate(model, glm::vec3(0.0f, altura, 0.0f));

    // Escalado
    model = glm::scale(model, glm::vec3(1.8f));

    // Rotación sobre su propio eje
    float angulo = factor * 360.0f;
    model = glm::rotate(model, glm::radians(angulo), glm::vec3(1, 0, 0));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    NPChacha_M.RenderModel();
}



void renderCasaHachaZim(glm::mat4& model, GLuint uniformModel, Model& casaZim, Model& hachaZim, float now)
{
    // Base: casa
    glm::mat4 modelCasa = glm::mat4(1.0f);
    modelCasa = glm::translate(modelCasa, glm::vec3(60.5f, 0.0f, -170));
    modelCasa = glm::rotate(modelCasa, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelCasa = glm::scale(modelCasa, glm::vec3(18.0f, 18.0f, 18.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCasa));
    casaZim.RenderModel();

    float angulo = sin(now * 4.0f) * glm::radians(45.0f);  // MISMO ángulo para ambas

    // Hacha 1
    glm::mat4 modelHacha1 = glm::translate(modelCasa, glm::vec3(0.7f, 1.8f, 0.0f));
    modelHacha1 = glm::rotate(modelHacha1, angulo, glm::vec3(0.0f, 0.0f, 1.0f));
    modelHacha1 = glm::scale(modelHacha1, glm::vec3(0.8f, 0.8f, 0.8f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelHacha1));
    hachaZim.RenderModel();

    // Hacha 2 
    glm::mat4 modelHacha2 = glm::translate(modelCasa, glm::vec3(-0.7f, 1.8f, 0.0f));
    modelHacha2 = glm::rotate(modelHacha2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelHacha2 = glm::rotate(modelHacha2, -angulo, glm::vec3(0.0f, 0.0f, 1.0f));  
    modelHacha2 = glm::scale(modelHacha2, glm::vec3(0.8f, 0.8f, 0.8f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelHacha2));
    hachaZim.RenderModel();

}





