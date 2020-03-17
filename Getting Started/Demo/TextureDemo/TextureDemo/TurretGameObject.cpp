#include "TurretGameObject.h"

TurretGameObject::TurretGameObject(glm::vec3& entityPos, GLuint entityTexture, GLuint turretTexture, GLint entityNumElements, GameObject& ref, void shoot(Weapon* w, glm::vec3 startingPos, double dx, double dy)) : GameObject(entityPos, entityTexture, entityNumElements), turretTex(turretTexture), player(ref) {
	objectSize = 2.0f;
	aimAngle = 90;
	shotCD = 3;
	shootGun = shoot;
	isFriendly = false;
}

void TurretGameObject::update(double deltaTime) {
	GameObject::update(deltaTime);
	shotCD = shotCD - deltaTime;
	glm::vec3 pos = player.getPosition();
	double angle = atan2(pos.y - position.y, pos.x - position.x) * 180 / PI;
	setAimAngle(angle);
	if (shotCD < 0.1) {
		//shoot(w, player->getPosition() + glm::vec3(0.05f, 0.5f, 0), 0, 1);
		double rad = glm::radians(angle);
		double x = cos(rad);
		double y = sin(rad);
		(*shootGun)(gun, getPosition(), x, y);
		shotCD = 2;
	}
}

void TurretGameObject::render(Shader& shader) {
	shader.setUniform1f("radius", 1.0);
	glBindTexture(GL_TEXTURE_2D, turretTex);
	//Get the spacing for the orbs and then the required matrices
	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), (float)aimAngle, glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f));
	glm::mat4 transformationMatrix = translationMatrix * rotationMatrix * scaleMatrix;
	shader.setUniformMat4("transformationMatrix", transformationMatrix);
	//Draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	GameObject::render(shader);
}