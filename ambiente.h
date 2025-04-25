#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Texture.h"
#include "Sphere.h"
#include "Model.h"

#include "Material.h"

void elementosAmbiente(glm::mat4 model, GLuint uniformModel, Model& banca, Model& basura, Model& lampara, Model& arbol, Model& pino);