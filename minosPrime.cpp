#include "minosPrime.h"

void renderMinos(glm::mat4 model, glm::mat4 modelaux, glm::mat4 modelauxCuerpo, GLuint uniformModel, std::vector<Model*> listaModelosMinos, glm::vec3 pos, GLfloat angulo, GLfloat anguloAnimacion) {
	Model* minosUpperRightArm = listaModelosMinos[0];
	Model* minosUpperLeftArm = listaModelosMinos[1];
	Model* minosRightThigh = listaModelosMinos[2];
	Model* minosRightLeg = listaModelosMinos[3];
	Model* minosLowerRightHand = listaModelosMinos[4];
	Model* minosLowerLeftArm = listaModelosMinos[5];
	Model* minosLeftThigh = listaModelosMinos[6];
	Model* minosLeftLeg = listaModelosMinos[7];
	Model* minosHead = listaModelosMinos[8];
	Model* minosBody = listaModelosMinos[9];

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, angulo, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
	modelaux = model;

	//Cuerpo
	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, -.3f, 0.f));
	modelauxCuerpo = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosBody->RenderModel();

	//Cabeza
	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, .15f, 0.f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosHead->RenderModel();

	//Brazo derecho 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(-0.15f, .32f, 0.f));
	model = glm::rotate(model, sin(glm::radians(-anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosUpperRightArm->RenderModel();

	//Brazo derecho 1
	model = glm::translate(model, glm::vec3(-0.05f, -.1f, 0.f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosLowerRightHand->RenderModel();

	//Brazo izquierdo 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(0.15f, .32f, 0.f));
	model = glm::rotate(model, sin(glm::radians(anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosUpperLeftArm->RenderModel();

	//Brazo izquierdo 1
	model = glm::translate(model, glm::vec3(0.03f, -.13f, 0.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosLowerLeftArm->RenderModel();

	//Pierna derecho 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(-0.06f, -.01f, 0.f));
	model = glm::rotate(model, sin(glm::radians(anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosRightThigh->RenderModel();

	//Pierna derecho 1
	model = glm::translate(model, glm::vec3(-0.0f, -.2f, 0.f));
	model = glm::rotate(model, sin(glm::radians(-anguloAnimacion)) / 2.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosRightLeg->RenderModel();

	//Pierna izquierda 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(0.06f, -.01f, 0.f));
	model = glm::rotate(model, sin(glm::radians(-anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosRightThigh->RenderModel();

	//Pierna izquierda 1
	model = glm::translate(model, glm::vec3(-0.0f, -.2f, 0.f));
	model = glm::rotate(model, sin(glm::radians(anguloAnimacion)) / 2.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosRightLeg->RenderModel();

	glDisable(GL_BLEND);
}
void renderMinosVenas(glm::mat4 model, glm::mat4 modelaux, glm::mat4 modelauxCuerpo, GLuint uniformModel, std::vector<Model*> minosVeinsModelsList, glm::vec3 pos, GLfloat angulo, GLfloat anguloAnimacion) {
	Model* minosVeinsUpperRightArm = minosVeinsModelsList[0];
	Model* minosVeinsUpperLeftArm = minosVeinsModelsList[1];
	Model* minosVeinsRightThigh = minosVeinsModelsList[2];
	Model* minosVeinsRightLeg = minosVeinsModelsList[3];
	Model* minosVeinsLowerRightArm = minosVeinsModelsList[4];
	Model* minosVeinsLowerLeftArm = minosVeinsModelsList[5];
	Model* minosVeinsLeftThigh = minosVeinsModelsList[6];
	Model* minosVeinsLeftLeg = minosVeinsModelsList[7];
	Model* minosVeinsBody = minosVeinsModelsList[8];
	Model* corazonMinos = minosVeinsModelsList[9];
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	model = glm::mat4(1.0f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, angulo, glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, glm::vec3(5.f, 5.f, 5.f));
	modelaux = model;
	model = glm::rotate(model, glm::radians(-90.f), glm::vec3(1.0f, 0.0f, .0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	corazonMinos->RenderModel();

	//Venas
	model = modelaux;
	model = glm::translate(model, glm::vec3(0.0f, -0.05f, 0.f));
	modelauxCuerpo = model;
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsBody->RenderModel();


	//Brazo derecho 0
	model = glm::translate(model, glm::vec3(0.0f, -0.25f, 0.f));
	modelauxCuerpo = model;
	model = glm::translate(model, glm::vec3(-0.15f, .32f, 0.f));
	model = glm::rotate(model, sin(glm::radians(-anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsUpperRightArm->RenderModel();


	//Brazo derecho 1
	model = glm::translate(model, glm::vec3(-0.05f, -.1f, 0.f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, .0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsLowerRightArm->RenderModel();

	//Brazo izquierdo 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(0.15f, .32f, 0.f));
	model = glm::rotate(model, sin(glm::radians(anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsUpperLeftArm->RenderModel();


	//Brazo izquierdo 1
	model = glm::translate(model, glm::vec3(0.03f, -.13f, 0.f));
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, .0f));

	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsLowerLeftArm->RenderModel();


	//Pierna derecho 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(-0.06f, -.01f, 0.f));
	model = glm::rotate(model, sin(glm::radians(anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsRightThigh->RenderModel();


	//Pierna derecho 1
	model = glm::translate(model, glm::vec3(-0.0f, -.2f, 0.f));
	model = glm::rotate(model, sin(glm::radians(-anguloAnimacion)) / 2.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsRightLeg->RenderModel();


	//Pierna izquierda 0
	model = modelauxCuerpo;
	model = glm::translate(model, glm::vec3(0.06f, -.01f, 0.f));
	model = glm::rotate(model, sin(glm::radians(-anguloAnimacion)) / 1.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsRightThigh->RenderModel();


	//Pierna izquierda 1
	model = glm::translate(model, glm::vec3(-0.0f, -.2f, 0.f));
	model = glm::rotate(model, sin(glm::radians(anguloAnimacion)) / 2.5f, glm::vec3(1.0f, 0.0f, 0.0f));
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
	minosVeinsRightLeg->RenderModel();


	glDisable(GL_BLEND);
}