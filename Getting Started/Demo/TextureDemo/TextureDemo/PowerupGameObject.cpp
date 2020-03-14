#include "PowerupGameObject.h"

PowerUpGameObject::PowerUpGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, PowerUpType powerUpType) : GameObject(entityPos, entityTexture, entityNumElements), type(powerUpType) {
	objectSize = 0.75f;
	isFriendly = true;
}

char* PowerUpGameObject::whatIs() {
	return "powerUp";
}

PowerUpType PowerUpGameObject::getPowerUpType() {
	return type;
}