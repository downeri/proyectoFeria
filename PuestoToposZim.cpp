#include "PuestoToposZim.h"
#include <glew.h>
#include <glfw3.h>
#include <unordered_map>

#include <glm.hpp>                 
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Model.h"              
               

//  variables globales definidas aquí 
float       anguloMartillo = 0.0f;
const float angMin = -90.0f;



// Puesto de Topos (jaulas) 
void renderPuestoToposZim(glm::mat4 model, GLuint uniformModel, Model& puestoTopos)
{
    float z = -10.0f;
    for (int i = 0; i < 12; ++i)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(-20.0f, 0.0f, z));
        model = glm::scale(model, glm::vec3(0.8f));
        model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        puestoTopos.RenderModel();
        z += 5.0f;
    }
}

//  Cerdito (cuerpo + ojos, controlados por tiempo)
void renderNPCPuestoToposZim(glm::mat4 model,
    GLuint uniformModel,
    Model& npcToposCuerpo)
{
    // ---------- Transformación común ----------
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-20.0f, 0.0f, -17.0f));
    model = glm::scale(model, glm::vec3(5.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    // ---------- 1) cuerpo ----------
    npcToposCuerpo.RenderModel();

    // ---------- 2) ojos sincronizados con el martillo ----------
    bool fueGolpeado = (anguloMartillo <= angMin + 5.0f);
    if (fueGolpeado)
        CerditoOjosX_M.RenderModel();
    else
        CerditoOjosNorm_M.RenderModel();
}




// Martillo animado 
void renderNPCMartilloPuestoToposZim(glm::mat4 model,
    GLuint uniformModel,
    Model& npcMartilloTopos)
{
    static bool  bajando = true;
    const  float angMax = -10.0f;
    const  float velDeg = 90.0f;

    static double lastT = glfwGetTime();
    double now = glfwGetTime();
    float  dt = static_cast<float>(now - lastT);
    lastT = now;

    if (bajando) {
        anguloMartillo -= velDeg * dt;
        if (anguloMartillo <= angMin) bajando = false;
    }
    else {
        anguloMartillo += velDeg * dt;
        if (anguloMartillo >= angMax) bajando = true;
    }

    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(-20.0f, 0.0f, -25.0f));
    model = glm::rotate(model, glm::radians(anguloMartillo), glm::vec3(-1, 0, 0));
    model = glm::scale(model, glm::vec3(5.5f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    npcMartilloTopos.RenderModel();
}

