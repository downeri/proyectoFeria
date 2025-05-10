#include "dados.h"

int animacion = 0;
float movimientoDados = 0.0f;

void renderJuegoDados(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, Mesh& piso, Texture& pisoTextura, float posicionX, float posicionZ, GLboolean getEPressed, float deltaTime) {
	glm::vec3 posicion = glm::vec3(-20.0f, -1.0f, -250.0f);

	model = glm::mat4(1.0);
	model = glm::translate(model, posicion);
	model = glm::scale(model, glm::vec3(1.5f, 1.5f, 4.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[0]->RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x - 6.0f, posicion.y, posicion.z));
	model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaModelos[3]->RenderModel();

	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posicion.x, posicion.y + 0.2f, posicion.z));
	model = glm::scale(model, glm::vec3(0.9f, 1.0f, 2.4f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	pisoTextura.UseTexture();
	piso.RenderMesh();

	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, -15.0f));
	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, -5.0f));
	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, 5.0f));
	renderMesaDados(model, uniformModel, *listaModelos[1], posicion, glm::vec3(0.0f, 0.0f, 15.0f));

	if (animacion == 0 && getEPressed) {
		if ((posicionX > -25.0f && posicionX < -10.0f) && (posicionZ > -270.0f && posicionZ < -260.0f))
			animacion = 1;
		if ((posicionX > -25.0f && posicionX < -10.0f) && (posicionZ > -260.0f && posicionZ < -250.0f))
			animacion = 2;
		if ((posicionX > -25.0f && posicionX < -10.0f) && (posicionZ > -250.0f && posicionZ < -240.0f))
			animacion = 3;
		if ((posicionX > -25.0f && posicionX < -10.0f) && (posicionZ > -240.0f && posicionZ < -230.0f))
			animacion = 4;
	}
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.3f, -15.0f), 1, deltaTime);
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.3f, -5.0f), 2, deltaTime);
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.3f, 5.0f), 3, deltaTime);
	renderDados(model, uniformModel, *listaModelos[2], posicion, glm::vec3(0.0f, 2.3f, 15.0f), 4, deltaTime);

}

void renderMesaDados(glm::mat4 model, GLuint uniformModel, Model &mesaDados, glm::vec3 position, glm::vec3 translate) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x+translate.x, position.y+translate.y, position.z+translate.z));
	model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	mesaDados.RenderModel();
}

void renderDados(glm::mat4 model, GLuint uniformModel, Model& dados, glm::vec3 position, glm::vec3 translate, int mesa, float deltaTime) {
	if (animacion != mesa) {
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(position.x + translate.x + 0.5, position.y + translate.y, position.z + translate.z - 0.5));
		model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dados.RenderModel();
		model = glm::translate(model, glm::vec3(-1.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dados.RenderModel();
	}
	else {
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(position.x + translate.x + 0.5, position.y + translate.y + (5.0f * sin(glm::radians(movimientoDados))), position.z + translate.z - 0.5));
		model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		model = glm::rotate(model, glm::radians(movimientoDados * 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dados.RenderModel();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(position.x + translate.x - 0.75, position.y + translate.y + (5.0f * sin(glm::radians(movimientoDados))), position.z + translate.z + 0.75));;
		model = glm::scale(model, glm::vec3(1.25f, 1.25f, 1.25f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(movimientoDados * 2.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dados.RenderModel();

		movimientoDados += 1.0f * deltaTime;
		if (movimientoDados >= 180.0f) {
			movimientoDados = 0;
			animacion = 0;
		}
	}
	
}