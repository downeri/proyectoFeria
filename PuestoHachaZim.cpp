#include "PuestoHachaZim.h"
#include <gtc/type_ptr.hpp>
#include "Window.h"
#include "Camera.h"
#include <iostream>        


bool lanzarHacha = false;
float movimientoHacha = 0.0f;
glm::vec3 posicionInicioHacha = glm::vec3(30.5f, 1.35f, -198.0f); 
bool lanzamientoEnProgreso = false;


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
    float angulo = glm::radians(sin(tiempo * 2.0f) * 60.0f); 

    model = glm::translate(model, glm::vec3(-0.2f, 1.0f, 0.0f)); 

    model = glm::rotate(model, angulo, glm::vec3(0.0f, 0.0f, 1.0f)); 

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    brazoDib.RenderModel();
}




extern Model NPChacha_M;

void renderHachaLanzada(glm::mat4 modelNPC, GLuint uniformModel, float factor) {
    glm::mat4 model = modelNPC;

    model = glm::translate(model, glm::vec3(-0.5f, 1.35f, 0.65f));

    float altura = factor * 2.0f;  
    model = glm::translate(model, glm::vec3(0.0f, altura, 0.0f));

    model = glm::scale(model, glm::vec3(1.8f));

    float angulo = factor * 360.0f;
    model = glm::rotate(model, glm::radians(angulo), glm::vec3(1, 0, 0));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    NPChacha_M.RenderModel();
}



void renderCasaHachaZim(glm::mat4& model, GLuint uniformModel, Model& casaZim, Model& hachaZim, float now)
{
    glm::mat4 modelCasa = glm::mat4(1.0f);
    modelCasa = glm::translate(modelCasa, glm::vec3(60.5f, 0.0f, -170));
    modelCasa = glm::rotate(modelCasa, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelCasa = glm::scale(modelCasa, glm::vec3(18.0f, 18.0f, 18.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelCasa));
    casaZim.RenderModel();

    float angulo = sin(now * 4.0f) * glm::radians(45.0f); 

    glm::mat4 modelHacha1 = glm::translate(modelCasa, glm::vec3(0.7f, 1.8f, 0.0f));
    modelHacha1 = glm::rotate(modelHacha1, angulo, glm::vec3(0.0f, 0.0f, 1.0f));
    modelHacha1 = glm::scale(modelHacha1, glm::vec3(0.8f, 0.8f, 0.8f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelHacha1));
    hachaZim.RenderModel();

    glm::mat4 modelHacha2 = glm::translate(modelCasa, glm::vec3(-0.7f, 1.8f, 0.0f));
    modelHacha2 = glm::rotate(modelHacha2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    modelHacha2 = glm::rotate(modelHacha2, -angulo, glm::vec3(0.0f, 0.0f, 1.0f));  
    modelHacha2 = glm::scale(modelHacha2, glm::vec3(0.8f, 0.8f, 0.8f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(modelHacha2));
    hachaZim.RenderModel();

}

void renderHachaVoladora(GLuint uniformModel, Model& hacha,

    float deltaTime, Camera& cam)
{
    deltaTime = glm::clamp(deltaTime, 0.0f, 0.016f); 

    if (!lanzarHacha) return;

    static glm::vec3 origen;
    static bool  iniciado = false;
    static float avance = 0.0f;
    static float spin = 0.0f;

    if (!iniciado) {
        glm::vec3 frente = glm::normalize(cam.getCameraDirection());
        origen = cam.getCameraPosition() + frente * 10.5f;
        origen.y = cam.getCameraPosition().y - 0.5f;
        iniciado = true;
        avance = 0.0f;
        spin = 0.0f;
    }

    const float velocidad = 17.5f;
    avance += velocidad * deltaTime;

    glm::vec3 frenteXZ = glm::normalize(glm::vec3(
        cam.getCameraDirection().x, 0.0f,
        cam.getCameraDirection().z));
    glm::vec3 pos = origen + frenteXZ * avance;

    const float vueltasPorSegundo = 1.6f;
    spin += vueltasPorSegundo * glm::two_pi<float>() * deltaTime;

    glm::mat4 model(1.0f);
    model = glm::translate(model, pos);

    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

    float yaw = atan2(frenteXZ.x, frenteXZ.z);
    model = glm::rotate(model, yaw, glm::vec3(0, 1, 0));

    model = glm::rotate(model, spin, glm::vec3(0, 0, 1));

    model = glm::scale(model, glm::vec3(3.5f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    hacha.RenderModel();

    if (avance >= 30.0f) {
        lanzarHacha = false;
        lanzamientoEnProgreso = false;
        iniciado = false;
    }
}









