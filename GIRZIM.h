#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>
#include "Model.h"

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>


void renderGirZim(glm::mat4 model, GLuint uniformModel,
    Model& tronco_M, Model& cabeza_M,
    Model& brazo1_M, Model& brazo2_M,
    Model& pierna1_M, Model& pierna2_M,
    float now);
