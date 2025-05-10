#include "PuestoPizzaZim.h"

void renderPuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& puestoPizza) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -175.0f));
    model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    puestoPizza.RenderModel();
}


void renderNPCOjosPizzaZim(glm::mat4 model, GLuint uniformModel, float tiempo) {
    model = glm::mat4(1.0f);

    // Posición base de los ojos (ajústala si es necesario)
    model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -175.0f));
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    // Parpadeo: cambia cada 0.5 segundos
    int periodo = static_cast<int>(tiempo * 2.0f) % 2; // alterna entre 0 y 1

    if (periodo == 0) {
        NPCOjosabiertos_M.RenderModel();
    }
    else {
        NPCOjoscerrados_M.RenderModel();
    }
}



void renderNPCPuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& npcPizza) {
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-30.0f, 0.0f, -175.0f));//x, y, z
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    npcPizza.RenderModel();
}

void renderNPCBrazo1PuestoPizzaZim(glm::mat4 model, GLuint uniformModel, Model& NPCbrazo1Pizza, float tiempo) {
    model = glm::mat4(1.0f);

    // Movimiento hacia arriba y abajo, ajusta amplitud y velocidad
    float angulo = sin(tiempo * 2.0f) * glm::radians(45.0f); // Oscila entre -45° y +45°

    model = glm::translate(model, glm::vec3(-30.95f, 4.9f, -176.9f)); // posición base
    model = glm::rotate(model, angulo, glm::vec3(0.0f, 0.0f, 1.0f)); // rotación tipo bisagra (eje X)
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 0, 1));
    model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    NPCbrazo1Pizza.RenderModel();
}


