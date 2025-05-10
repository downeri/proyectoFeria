#include "boliche.h"
#include "utilities.h"

void renderBoliche(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, std::vector<Mesh*> bowlingMeshList, std::vector<Texture*> listaTexturas, GLboolean ePressed, glm::vec3 modelPosition, GLfloat* bowlingAnimationLane, GLfloat deltaTime) {
	GLfloat altura = -123.f;

	renderBuilding(model, uniformModel, bowlingMeshList, listaTexturas, glm::vec3(0.0f,altura,0.0f));

	GLfloat z = 45.0f;
	for (int i = 0; i < 7;i++) {
		renderRailing(model, uniformModel, *listaModelos[5], glm::vec3(30.0f, altura, z-5.0f));
		if (bowlingAnimationLane[i] == 0.0f) renderPines(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, z));
		renderRailing(model, uniformModel, *listaModelos[5], glm::vec3(30.0f, altura, z + 5.0f));
		renderLaneFloor(model, uniformModel, *listaModelos[6], glm::vec3(35.0f, altura + 0.01f, z));

		renderTerminal(model, uniformModel, *listaModelos[2], glm::vec3(10.0f, altura + 3.0, z + 7.0f));
		if (twoPointsDistance(modelPosition, glm::vec3(10.0f, altura + 3.0, z + 7.0f)) < 5.0f && ePressed) {
			bowlingAnimationLane[i] = 0.01;
		} 
		renderTable(model, uniformModel, *listaModelos[3], glm::vec3(-14.0f, altura, z));

		renderChair(model, uniformModel, *listaModelos[9], glm::vec3(-19.0f, altura + 2.0f, z + 1.5f), 0.0f);
		renderChair(model, uniformModel, *listaModelos[9], glm::vec3(-14.0f, altura + 2.0f, z + 5.f), 90.0f);
		renderChair(model, uniformModel, *listaModelos[9], glm::vec3(-15.0f, altura + 2.0f, z - 5.f), -90.0f);

		if (bowlingAnimationLane[i]>0.0f) {
			bowlingAnimationLane[i] += 0.2f * deltaTime;
			if (bowlingAnimationLane[i] <= 40.0f) renderPines(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, z));
			else if (10.0f + bowlingAnimationLane[i] > 40.0f) renderPinesAnimation(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, z), bowlingAnimationLane[i]*1.8f);
			if (10.0f + bowlingAnimationLane[i]>=100.0f) bowlingAnimationLane[i] = 0.0f;
			renderMauriceBowling(model, uniformModel, *listaModelos[1], glm::vec3(10.0f + bowlingAnimationLane[i], altura + 1.0f, z), bowlingAnimationLane[i]*20.0f);
		}

		if(i%2==0) renderChandelier(model, uniformModel, *listaModelos[4], glm::vec3(0.f, altura + 20, z));
		z = z - 15.0f;
	}
	renderCarpet(model, uniformModel, *listaModelos[7], glm::vec3(-14.0f, altura + 0.1f, 10.0f));
	renderCerberusStatue(model, uniformModel, *listaModelos[8], glm::vec3(10, altura + 0.1f, 57.0f));
	renderCerberusStatue(model, uniformModel, *listaModelos[8], glm::vec3(10, altura + 0.1f, -57.0f));

}

void renderPines(glm::mat4 model, GLuint uniformModel, Model& idol, glm::vec3 posInicial) {

	//1
	model = glm::mat4(1.0);
	model = glm::translate(model, posInicial);
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//2,1
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 1.0f, posInicial.y, posInicial.z+0.6f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//2,2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 1.0f, posInicial.y, posInicial.z - .6f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//3,1
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 2.0f, posInicial.y, posInicial.z - 1.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//3,2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 2.0f, posInicial.y, posInicial.z ));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//3,3
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 2.0f, posInicial.y, posInicial.z+ 1.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,1
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z - 1.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z - 0.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,3
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z + 0.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,4
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z + 1.5f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();
}

void renderPinesAnimation(glm::mat4 model, GLuint uniformModel, Model& idol, glm::vec3 posInicial, GLfloat rotation) {
	if (rotation > 90.0f) rotation = 90.0f;
	//1
	model = glm::mat4(1.0);
	model = glm::translate(model, posInicial);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//2,1
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 1.0f, posInicial.y, posInicial.z + 0.6f));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(0.3f, 0.0f, 0.67f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//2,2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 1.0f, posInicial.y, posInicial.z - .6f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(-0.5f, 0.0f, -0.2f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//3,1
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 2.0f, posInicial.y, posInicial.z - 1.0f));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(0.8f, 0.0f, -0.4f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//3,2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 2.0f, posInicial.y, posInicial.z));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(-0.1f, 0.0f, 0.9f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//3,3
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 2.0f, posInicial.y, posInicial.z + 1.0f));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(0.6f, 0.0f, 0.3f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,1
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z - 1.5f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(-0.75f, 0.0f, 0.15f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,2
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z - 0.5f));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(0.45f, 0.0f, -0.6f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,3
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z + 0.5f));
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.25f, 0.0f, 0.88f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();

	//4,4
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(posInicial.x + 3.0f, posInicial.y, posInicial.z + 1.5f));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(-0.35f, 0.0f, 0.7f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	idol.RenderModel();
}


void renderTerminal(glm::mat4 model,GLuint uniformModel, Model& terminal, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(8.f, 8.f, 8.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	terminal.RenderModel();
}

void renderLaneFloor(glm::mat4 model, GLuint uniformModel, Model& laneFloor, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(.8f, .3f, .7f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	laneFloor.RenderModel();
}

void renderMauriceBowling(glm::mat4 model, GLuint uniformModel, Model& maurice, glm::vec3 position, GLfloat rotation) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(position));
	model = glm::scale(model, glm::vec3(.3f, .3f, .3f));
	model = glm::rotate(model, glm::radians(-rotation), glm::vec3(.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	maurice.RenderModel();

}

void renderCarpet(glm::mat4 model, GLuint uniformModel, Model& carpet, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(18.0f, 1.f, 28.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	carpet.RenderModel();
}

void renderCerberusStatue(glm::mat4 model, GLuint uniformModel, Model& cerberusStatue, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(2.0f, 2.f, 2.0f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	cerberusStatue.RenderModel();
}

void renderTable(glm::mat4 model, GLuint uniformModel, Model& table, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	table.RenderModel();
}

void renderChandelier(glm::mat4 model, GLuint uniformModel, Model& chandelier, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	chandelier.RenderModel();
	glDisable(GL_BLEND);
}

void renderRailing(glm::mat4 model, GLuint uniformModel, Model& railing, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(1.8f, 1.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	railing.RenderModel();
	glDisable(GL_BLEND);
}

void renderBuilding(glm::mat4 model, GLuint uniformModel, std::vector<Mesh*> bowlingMeshList, std::vector<Texture*> listaTexturas, glm::vec3 position){
	//Piso
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(7.0f, 1.0f, 6.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	listaTexturas[0]->UseTexture();

	bowlingMeshList[0]->RenderMesh();

	//Techo
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, position.y+20, 0.0f));
	model = glm::scale(model, glm::vec3(7.0f, 1.0f, 6.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	listaTexturas[0]->UseTexture();

	bowlingMeshList[0]->RenderMesh();

	//Muro derecho boliche
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, position.y, 60.0f));
	model = glm::scale(model, glm::vec3(140.0f, 20.0f, 1.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	bowlingMeshList[1]->RenderMesh();
	

	//Muro izquierdo boliche
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(0.0f, position.y, -60.0f));
	model = glm::scale(model, glm::vec3(140.0f, 20.0f, 1.0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

	bowlingMeshList[1]->RenderMesh();

	//Muro trasero boliche
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(50.0f, position.y+5.0f, 0.0f));
	model = glm::scale(model, glm::vec3(.0f, 15.0f, 130.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bowlingMeshList[1]->RenderMesh();

	//Muro Frontal boliche
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-55.0f, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(.0f, 20.0f, 130.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bowlingMeshList[1]->RenderMesh();

	//Muro trasero boliche negro
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(55.0f, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(.0f, 20.0f, 130.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	listaTexturas[1]->UseTexture();
	bowlingMeshList[1]->RenderMesh();
}

void renderChair(glm::mat4 model, GLuint uniformModel, Model& chair, glm::vec3 position, GLfloat angle) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(2.0f, 2.f, 2.0f));
	model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	chair.RenderModel();
}
