#include "boliche.h"


void renderBoliche(glm::mat4 model, GLuint uniformModel, std::vector<Model*> listaModelos, std::vector<Mesh*> bowlingMeshList, std::vector<Texture*> listaTexturas) {
	GLfloat altura = -120.0f;

	renderBuilding(model, uniformModel, bowlingMeshList, listaTexturas, glm::vec3(0.0f,altura,0.0f));
	renderPines(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, 40.0f));
	renderPines(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, 15.0f));
	renderPines(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, -10.0f));
	renderPines(model, uniformModel, *listaModelos[0], glm::vec3(50.0f, altura, -35.0f));

	renderTerminal(model, uniformModel, *listaModelos[2], glm::vec3(10.0f, altura + 2.5, 45.0f));
	renderTerminal(model, uniformModel, *listaModelos[2], glm::vec3(10.0f, altura + 2.5, 20.0f));
	renderTerminal(model, uniformModel, *listaModelos[2], glm::vec3(10.0f, altura + 2.5, -5.0f));
	renderTerminal(model, uniformModel, *listaModelos[2], glm::vec3(10.0f, altura + 2.5, -30.0f));

	renderTable(model, uniformModel, *listaModelos[3], glm::vec3(-14.0f, altura, 40.0f));
	renderTable(model, uniformModel, *listaModelos[3], glm::vec3(-14.0f, altura, 15.0f));
	renderTable(model, uniformModel, *listaModelos[3], glm::vec3(-14.0f, altura, -10.0f));
	renderTable(model, uniformModel, *listaModelos[3], glm::vec3(-14.0f, altura, -35.0f));

	renderChandelier(model, uniformModel, *listaModelos[4], glm::vec3(0.f, altura+20, .0f));
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

void renderTerminal(glm::mat4 model,GLuint uniformModel, Model& terminal, glm::vec3 position) {
	model = glm::mat4(1.0);
	model = glm::translate(model, position);
	model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));
	model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	terminal.RenderModel();
}

void renderMauriceBowling(glm::mat4 model, GLuint uniformModel, Model& maurice) {
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(5.0f, 1.0f, 0.0));
	model = glm::scale(model, glm::vec3(.2f, .3f, .3f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	maurice.RenderModel();

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
	model = glm::translate(model, glm::vec3(70.0f, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(.0f, 20.0f, 130.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bowlingMeshList[1]->RenderMesh();

	//Muro Frontal boliche
	model = glm::mat4(1.0);
	model = glm::translate(model, glm::vec3(-70.0f, position.y, 0.0f));
	model = glm::scale(model, glm::vec3(.0f, 20.0f, 130.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	bowlingMeshList[1]->RenderMesh();

}