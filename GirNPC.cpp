#include "GirNPC.h"
#include <glew.h>
#include <glfw3.h>
#include <unordered_map>

#include <glm.hpp>                 
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Model.h"     

// ─── Modelos que ya cargaste en main.cpp ─────────────────────────────
extern Model troncoZIM_M;
extern Model cabezaZIM_M;
extern Model brazo1ZIM_M;   // el brazo que quieres animar
// ────────────────────────────────────────────────────────────────────

void renderGirNPC(glm::vec3 posBase,
    GLuint uniformModel,
    float deltaTime,
    float now)
{
    //------------------ 1. MATRIZ BASE : tronco ----------------------
    glm::mat4 base = glm::translate(glm::mat4(1.0f), posBase);
    base = glm::rotate(base, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f)); // ROTACIÓN GLOBAL
    base = glm::scale(base, glm::vec3(10.2f)); // escala global


    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(base));
    troncoZIM_M.RenderModel();

    //------------------ 2. CABEZA : giro continuo --------------------
    glm::mat4 cabeza = base;
    cabeza = glm::translate(cabeza, glm::vec3(0.0f, 0.25f, -0.04f)); // pivote cuello
    cabeza = glm::rotate(cabeza,
        now * glm::radians(90.0f),               // 90°/seg
        glm::vec3(0.0f, 1.0f, 0.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(cabeza));
    cabezaZIM_M.RenderModel();

    //------------------ 3. BRAZO : saludo oscilante ------------------
    // variables estáticas para conservar ángulo
    static float ang = 0.0f;          // radianes
    static float dir = 1.0f;          // 1 = sube, -1 = baja

    const float velBrazo = glm::radians(20.0f);       // 90°/seg
    const float angMax = glm::radians(60.0f);      // límite superior
    const float angMin = glm::radians(-10.0f);      // límite inferior

    ang += dir * velBrazo * deltaTime;
    if (ang >= angMax) { ang = angMax; dir = -1.0f; }
    if (ang <= angMin) { ang = angMin; dir = 1.0f; }

    glm::mat4 brazo = base;
    brazo = glm::translate(brazo, glm::vec3(0.0f, 0.18, 0.02f)); // hombro
    brazo = glm::rotate(brazo, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    brazo = glm::rotate(brazo, ang, glm::vec3(1.0f, 0.0f, 0.0f)); // arriba/abajo

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(brazo));
    brazo1ZIM_M.RenderModel();
}
