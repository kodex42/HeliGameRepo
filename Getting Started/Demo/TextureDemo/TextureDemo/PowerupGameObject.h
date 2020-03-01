#pragma once

#include "GameObject.h"

// Inherits from GameObject
class PowerUpGameObject : public GameObject {
public:
	PowerUpGameObject(glm::vec3& entityPos, GLuint entityTexture, GLint entityNumElements, PowerUpType powerUpType);

	// Member functions
	char* whatIs();
	PowerUpType getType();

private:
	// Data members
	PowerUpType type;
};