#pragma once
#include <glm.hpp>
#include <glew.h>

// Dibuja al cerdito animado
void renderGirNPC(glm::vec3 posicionBase,   // dónde colocar todo el cuerpo
    GLuint uniformModel,
    float deltaTime,
    float tiempoGlobal);
