#include "bateo.h"
#include "boliche.h"


void renderBatting(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, std::vector<Mesh*> meshList, std::vector<Texture*> listaTexturas) {
	glm::vec3 position = glm::vec3(90.0f, 0.0f, -200.0f);
	renderBattingBuilding(model, uniformModel, meshList, listaTexturas, position);
	float z = 35.0f;
	for (int i = 0;i < 4;i++) {
		renderCerberusPitcher(model, uniformModel, *listaModelos[0], glm::vec3(position.x + 45.0f, position.y + 4.5f, position.z + z));
		renderLava(model, uniformModel, *meshList[2], *listaTexturas[2], glm::vec3(position.x + 20.0f, position.y + .1f, position.z + z));
		renderTerminal(model, uniformModel, *listaModelos[3], glm::vec3(position.x - 2.0f, position.y + 3.5f, position.z + z + 8.0f));
		float xReja = 0.0f;
		for (int u = 0;u < 4;u++) {
			renderReja(model, uniformModel, *listaModelos[4], glm::vec3(position.x + 6.0f + xReja, position.y, position.z + z + 8.0f));
			renderReja(model, uniformModel, *listaModelos[4], glm::vec3(position.x + 6.0f + xReja, position.y, position.z + z - 8.0f));
			xReja += 12.5f;
		}
		z -= 25;
	}
	renderV1(model, uniformModel, *listaModelos[5], glm::vec3(position.x - 55.0f, position.y, position.z - 35.0f));
}

void renderBattingBuilding(glm::mat4 model, GLuint uniformModel, std::vector<Mesh*> meshList, std::vector<Texture*> listaTexturas, glm::vec3 position) {
	//Piso
	model = glm::mat4(1.0);
	model = glm::translate(model,position);
	model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaTexturas[0]->UseTexture();
	meshList[0]->RenderMesh();

	//Techo
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x, position.y+20.0f, position.z));
	model = glm::scale(model, glm::vec3(5.0f, 1.0f, 5.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaTexturas[0]->UseTexture();
	meshList[0]->RenderMesh();

	//Muro derecho
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z+50.0f));
	model = glm::scale(model, glm::vec3(100.0f, 20.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	listaTexturas[1]->UseTexture();
	meshList[1]->RenderMesh();

	//Muro izquierdo
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x, position.y, position.z - 50.0f));
	model = glm::scale(model, glm::vec3(100.0f, 20.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	meshList[1]->RenderMesh();

	//Muro trasero
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position.x+50.0f, position.y, position.z));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(100.0f, 20.0f, 1.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	meshList[1]->RenderMesh();


}

void renderFeedbacker(glm::mat4 model, GLuint uniformModel, Model& feedbacker) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 13.0f, 0.0));
	model = glm::scale(model, glm::vec3(20.f, 20.f, 20.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	feedbacker.RenderModel();
}

void renderOrbBall(glm::mat4 model, GLuint uniformModel, Model& cerberusOrb, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0));
	model = glm::scale(model, glm::vec3(0.001f, 0.001f, 0.001f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cerberusOrb.RenderModel();
}

void renderCerberusPitcher(glm::mat4 model, GLuint uniformModel, Model& cerberus, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(10.f, 10.f, 10.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cerberus.RenderModel();
}

void renderLava(glm::mat4 model, GLuint uniformModel, Mesh& lavaFloor, Texture& lavaTexture,glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(2.0f, 1.0f, .7f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	lavaTexture.UseTexture();
	lavaFloor.RenderMesh();
}

void renderReja(glm::mat4 model, GLuint uniformModel, Model& reja, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(11.0f, 16.0f, 10.f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	reja.RenderModel();
}

void renderV1(glm::mat4 model, GLuint uniformModel, Model& v1Ultrakill, glm::vec3 position) {
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::scale(model, glm::vec3(3.2f, 3.2f, 3.2f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	v1Ultrakill.RenderModel();
}