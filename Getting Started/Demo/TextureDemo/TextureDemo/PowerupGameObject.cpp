#include "PowerupGameObject.h"

PowerUpGameObject::PowerUpGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, PowerUpType powerUpType) : GameObject(entityPos, entityTexture, entityNumElements), type(powerUpType) {
	objectSize = 0.5f;
}

char* PowerUpGameObject::whatIs() {
	return "powerUp";
}

PowerUpType PowerUpGameObject::getType() {
	return type;
}